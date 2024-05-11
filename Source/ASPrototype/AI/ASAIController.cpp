// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ASAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "ASAI.h"
#include "Sound_tags.h"
//Ž�� ���
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h" //�þ�
#include "Perception/AISenseConfig_Hearing.h" //����
#include "Perception/AISense_Touch.h"//����

#include "Enemy/ASEnemyCharacter.h"
#include "Character/ASCharacterPlayer.h" //SetAngle ������

#include "Kismet/KismetMathLibrary.h" //charactor�� ������ 

//Ž�� ���� �߰�
#include "Components/WidgetComponent.h"
#include "UI/ASDetectWidget.h"

#include "Kismet/GameplayStatics.h"


AASAIController::AASAIController()
{	
	SetupPerception();

	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBAssetRef(TEXT("/Game/ASPrototype/Enemy/AI/BB_Enemy.BB_Enemy"));
	if (nullptr != BBAssetRef.Object)
	{
		BBAsset = BBAssetRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTAssetRef(TEXT("/Game/ASPrototype/Enemy/AI/BT_Enemy.BT_Enemy"));
	if (nullptr != BTAssetRef.Object)
	{
		BTAsset = BTAssetRef.Object;
	}


	//Detect Widget Component Setting 
	DetectBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("DetectWidget"));
	static ConstructorHelpers::FClassFinder<UUserWidget> DetectBarRef(TEXT("/Game/UI/WB_DetectBar_UI.WB_DetectBar_UI_C"));
	if (DetectBarRef.Class)
	{
		DetectBar->SetWidgetClass(DetectBarRef.Class);
		DetectBar->SetWidgetSpace(EWidgetSpace::Screen);
		DetectBar->SetDrawSize(FVector2D(150.0f, 15.0f));
		DetectBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	//�����ڿ����� Casting �ȵ� 
	//TSubclassOf<UUserWidget> WidgetObject = DetectBar->GetWidgetClass();
	//UASDetectWidget* uiRef = Cast<UASDetectWidget>(WidgetObject);
	//ensure(UiRef);
	//UiRef->SetOwner(this);

	//ID ���� 
	//AASEnemyBase* EnemyRef = Cast<AASEnemyBase>(GetPawn());
	//if (EnemyRef)
	//{
	//	TeamId = FGenericTeamId(EnemyRef->ID);
	//}

	AttackRange = 500.0f;
	DetectionLevel=0.0f;
	MaxLevel=1.0f;
	CurSituation = CurDetectSituation::NoneInRange;
}

void AASAIController::RunAI()
{
	UBlackboardComponent* BlackboardPtr = Blackboard.Get();
	if (UseBlackboard(BBAsset,BlackboardPtr))
	{	
		RunBehaviorTree(BTAsset);
		//bool RunResult = RunBehaviorTree(BTAsset);
		//ensure(RunResult);
	}
}

void AASAIController::StopAI()
{
	UBehaviorTreeComponent* BTComponent = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComponent)
	{
		BTComponent->StopTree();
	}
}

void AASAIController::CheckPlayer(AActor* player)
{	
	
	//�ӽ� : ���� �÷��̾ �ν� (������ �ν�X)
	if (player==NULL){ return; }
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Purple, FString::Printf(TEXT("CheckPlayer")));

	
	UiRef->AddToViewport();
	if (GetBB_Target())
	{
		SetBB_Target(nullptr); //������ �ϴ� ��Ȳ 
		StopDetection();
	}
	else
	{
		SetBB_Target(player); //���� �ϴ� ��Ȳ
		StartDetection();
	}

}

void AASAIController::IncreaseDetectionLVL()
{
	if (GetBB_IsDetect())
	{
		return;
	}

	if (DetectionLevel >= MaxLevel)
	{
		UiRef->SetRedColor();
		UiRef->BlinkBar(); 
		// delay 
		CurSituation = CurDetectSituation::TargetIsDetected;
		return;
	}
	float value = 0.01f;
	DetectionLevel = FMath::Clamp(DetectionLevel + value, 0.0f, MaxLevel);
	UiRef->SetPercent(DetectionLevel);
}

void AASAIController::DecreaseDetectionLVL()
{

	if (DetectionLevel <= 0.0f)
	{
		UiRef->OffVisible();
		CurSituation = CurDetectSituation::NoneInRange;
		//SetBB_IsDetect(false);
		return;
	}
	float value = -0.005f;
	DetectionLevel = FMath::Clamp(DetectionLevel + value, 0.0f, MaxLevel);
	UiRef->SetPercent(DetectionLevel);
}


void AASAIController::SetBB_LastKnownPosition(FVector vector)
{
	GetBlackboardComponent()->SetValueAsVector(BBKEY_LastKnownPosition,vector);
}

FVector AASAIController::GetBB_LastKnownPosition()
{
	return GetBlackboardComponent()->GetValueAsVector(BBKEY_LastKnownPosition);
}


//BB ������ ���� 
void AASAIController::SetBB_Target(UObject* actor)
{
	GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, actor);
}

UObject* AASAIController::GetBB_Target()
{
	return GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET);
}

void AASAIController::SetBB_IsDetect(bool b)
{	
	GetBlackboardComponent()->SetValueAsBool(BBKEY_IsDetect, b);
}

bool AASAIController::GetBB_IsDetect()
{	
	return GetBlackboardComponent()->GetValueAsBool(BBKEY_IsDetect);
}

void AASAIController::SetBB_IsAlert(bool b)
{
	GetBlackboardComponent()->SetValueAsBool(BBKEY_IsAlert,b);
}

bool AASAIController::GetBB_IsAlert()
{
	return GetBlackboardComponent()->GetValueAsBool(BBKEY_IsAlert);
}

void AASAIController::SetBB_PatrolLoc(FVector vector)
{
	GetBlackboardComponent()->SetValueAsVector(BBKEY_PATROLLOC, vector);
}

FVector AASAIController::GetBB_PatrolLoc()
{
	return GetBlackboardComponent()->GetValueAsVector(BBKEY_PATROLLOC);
}

void AASAIController::SetBB_PathLoc(FVector vector)
{
	GetBlackboardComponent()->SetValueAsVector(BBKEY_PathLOC, vector);
}

FVector AASAIController::GetBB_PathLoc()
{
	return GetBlackboardComponent()->GetValueAsVector(BBKEY_PathLOC);
}

void AASAIController::SetBB_AttackRange(FVector vector)
{
	GetBlackboardComponent()->SetValueAsVector(BBKEY_AttackRange, vector);
}

FVector AASAIController::GetBB_AttackRange()
{
	return GetBlackboardComponent()->GetValueAsVector(BBKEY_AttackRange);
}



void AASAIController::SetBB_CanShootTarget(bool b)
{
	GetBlackboardComponent()->SetValueAsBool(BBKEY_CanShootTarget, b);
}

bool AASAIController::GetBB_CanShootTarget()
{
	return GetBlackboardComponent()->GetValueAsBool(BBKEY_CanShootTarget);
}


void AASAIController::StartDetection()
{
	//UiRef->Onvisible();
	if (!GetBB_IsDetect()){ UiRef->Onvisible(); }
	CurSituation = CurDetectSituation::TargetInRange;
}

void AASAIController::StopDetection()
{	
	if (GetBB_IsDetect() == false) //�ĺ� �ȵ� ���¿�����  
	{
		CurSituation = CurDetectSituation::TargetGetOutOfRange;
	}
}

void AASAIController::On_Updated(AActor* DetectedPawn, const  FAIStimulus Stimulus)
{
	//if (GetBB_IsDetect()) return;

	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("On_Updated , EventOnBySound is %d"), EventOnBySound));
	
	auto SensedClass = UAIPerceptionSystem::GetSenseClassForStimulus(this, Stimulus);

	if (SensedClass== UAISense_Sight::StaticClass())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Sight Sense")));

		AASCharacterPlayer* CurPlayer = Cast<AASCharacterPlayer>(DetectedPawn);
		CheckPlayer(CurPlayer);
	}
	else if (SensedClass == UAISense_Hearing::StaticClass())
	{
		if (Stimulus.Tag == tags::lvl1_Sound_tag) //���� �Ҹ��� �ǽɻ��� 
		{
			GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Hearing Sense")));
		}
		else if (Stimulus.Tag == tags::lvl2_Sound_tag) //ū �Ҹ��� ������ ,AlretLVL =2
		{
			//300m�ݰ濡 �ִ� ��ó ���� �ִ� 3���� ����� ���� ( ���� ��ġ + �ǽ� ���� )
		}
		SetBB_IsAlert(false);  SetBB_IsAlert(true);
		LastKnownPosition = Stimulus.StimulusLocation;
	}
	else if (SensedClass == UAISense_Touch::StaticClass())
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("Touch Sense"))); 
		//��ġ�� ��밡 Player ĳ���� ���� �� ���, �ٷ� Player���� Focus On�� ��. ( UI�� ��� ���ǵ� 2�� UP )
		//ĳ���� �� ���� �Ѿ��̸� IsDetect==true
	}
}


//void AASAIController::On_Updated(TArray<AActor*> const& updated_Actors)
//{
//	
//	for (size_t i = 0; i < updated_Actors.Num(); i++)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT("On_Updated , EventOnBySound is %d"), EventOnBySound));
//		FActorPerceptionBlueprintInfo info;
//		AIPerComp->GetActorsPerception(updated_Actors[i], info);
//		for (size_t k = 0; k < info.LastSensedStimuli.Num(); k++)
//		{
//			FAIStimulus const stim = info.LastSensedStimuli[k];
//			if (stim.Tag==tags::lvl1_Sound_tag) //���� �Ҹ��� �ǽɻ��� 
//			{
//				EventOnBySound = true;
//				SetBB_IsAlert(true);
//				SetBB_LastKnownPosition(stim.StimulusLocation);
//			}
//			else if (stim.Tag == tags::lvl2_Sound_tag) //ū �Ҹ��� ���ݻ��� 
//			{
//				EventOnBySound = true;
//				SetBB_IsDetect(true);
//			}
//			else
//			{
//				EventOnBySound = false;
//				AASCharacterPlayer* CurPlayer = Cast<AASCharacterPlayer>(updated_Actors[i]);
//				CheckPlayer(CurPlayer);
//			}
//
//		}
//	}
//}



void AASAIController::OnPawnDetected(AActor* DetectedPawn, const  FAIStimulus Stimulus) //�� ���� ���ֺ��� ���� �߻� 
{
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("On_Sight_Updated")));
	AASCharacterPlayer* CurPlayer = Cast<AASCharacterPlayer>(DetectedPawn);
	//ensure(CurPlayer);
	CheckPlayer(CurPlayer);

}

//void AASAIController::OnPawnDetected(const TArray<AActor*>& DetectedPawns) //�� ���� ���ֺ��� ���� �߻� 
//{	
//	for (int32 i = 0; i < DetectedPawns.Num(); ++i)
//	{
//		AASCharacterPlayer* CurPlayer = Cast<AASCharacterPlayer>(DetectedPawns[i]);
//		//ensure(CurPlayer);
//		CheckPlayer(CurPlayer);
//	}
//}



AActor* AASAIController::GetPlayer()
{	
	AActor* Actor = Cast<AActor>(PlayerRef);
	return Actor;
}

void AASAIController::Tick(float DeltaTime)
{
	//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Green, FString::Printf(TEXT(" EventOnBySound is %d"), EventOnBySound));
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Blue, FString::Printf(TEXT("DetectionLevel : %f"), DetectionLevel));
	ensure(PlayerRef);
	if (CurSituation!=CurDetectSituation::NoneInRange)  //StartDetection() ȣ�� �� -> ����   ,   StopDetection() ȣ�� �� UI ������� -> ����
	{
		//UI ��ġ ����
		FRotator ControlRotator = GetControlRotation();
		FVector PlayerLoc = PlayerRef->GetActorLocation();
		FVector EnemyLoc = EnemyRef->GetActorLocation();
			
		FRotator ControllerRotator = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetControlRotation();
		FRotator IntervalRotator = UKismetMathLibrary::FindLookAtRotation(PlayerLoc, EnemyLoc);
		FRotator AngleRotator = UKismetMathLibrary::NormalizedDeltaRotator(IntervalRotator, ControllerRotator);
		float Angle = AngleRotator.Yaw;
		UiRef->SetAngle(Angle);

		//���� �÷��̾� ���� �Ÿ� ���
		FVector Location_Between_Player_And_Enemy = EnemyLoc - PlayerLoc;
		DistanceDifference_Value = Location_Between_Player_And_Enemy.Length();
	}

	//bool SuspicionTrigger=false;

	switch (CurSituation)
	{
	case CurDetectSituation::NoneInRange:
		break;
	case CurDetectSituation::TargetInRange:
		IncreaseDetectionLVL();
		break;
	case CurDetectSituation::TargetGetOutOfRange:
		if (DetectionLevel > 0.5f)
		{	
			DetectionLevel = 0.0f;
			CurSituation = CurDetectSituation::TargetIsSuspected;
			//SuspicionTrigger = true;
		}
		else 
		{
			DecreaseDetectionLVL();
		}
		break;
	case CurDetectSituation::TargetIsSuspected:
		SetBB_IsAlert(false); SetBB_IsAlert(true);
		LastKnownPosition = PlayerRef->GetActorLocation();
		UiRef->OffVisible();
		CurSituation = CurDetectSituation::NoneInRange;
		break;
	case CurDetectSituation::TargetIsDetected:
		SetBB_CanShootTarget(true);
		SetBB_IsDetect(true);
		//UiRef->OffVisible();
		CurSituation = CurDetectSituation::NoneInRange;
		break;
	default:
		break;
	}

	//�ǽɻ��´� PlayerGetOutOfRange ���¿��� �ѹ����� �ߵ� 

}

void AASAIController::BeginPlay()
{
	Super::BeginPlay();
	UiRef = Cast<UASDetectWidget>(DetectBar->GetUserWidgetObject());
	ensure(UiRef);
	UiRef->SetOwner(this);
	EnemyRef = Cast<AASEnemyCharacter>(GetPawn());
	ensure(EnemyRef);

	//�ٸ� Ŭ�������� �ɸ��� ��ü�� �� �޾ƿ�����, GetMesh() ȣ�� �� interface collision dataprovider����  ���� �߻�. 
	//USkeletalMeshComponent* mesh = EnemyRef->GetMesh();
	//QuestionMark->SetupAttachment(mesh);

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);
	PlayerRef = Cast<AASCharacterPlayer>(PlayerPawn);

	//ensure(PlayerRef);
}

void AASAIController::RangeSizeDown()
{
	FAISenseID Id = UAISense::GetSenseID(UAISense_Sight::StaticClass());

	auto Config = GetPerceptionComponent()->GetSenseConfig(Id);

	auto ConfigSight = Cast<UAISenseConfig_Sight>(Config);
	SightConfig->SightRadius = 500.f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
	GetPerceptionComponent()->RequestStimuliListenerUpdate();
}

void AASAIController::RangeSizeUP()
{
	FAISenseID Id = UAISense::GetSenseID(UAISense_Sight::StaticClass());

	auto Config = GetPerceptionComponent()->GetSenseConfig(Id);

	auto ConfigSight = Cast<UAISenseConfig_Sight>(Config);
	SightConfig->SightRadius = 1000.0f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
	GetPerceptionComponent()->RequestStimuliListenerUpdate();
}

UASDetectWidget* AASAIController::getWidget()
{
	return UiRef;
}


void AASAIController::SetupPerception()
{
	AIPerComp = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AI Perception Component"));
	
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SightConfig->SightRadius = 700.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 50.f;
		SightConfig->PeripheralVisionAngleDegrees = 90.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		AIPerComp->ConfigureSense(*SightConfig);
		AIPerComp->SetDominantSense(SightConfig->GetSenseImplementation());
		//AIPerComp->OnTargetPerceptionUpdated.AddDynamic(this, &AASAIController::OnPawnDetected);
	}
	HearingConfig = CreateDefaultSubobject<UAISenseConfig_Hearing>(TEXT("Hearing Config"));
	if (HearingConfig)
	{
		//hearid = HearingConfig->GetSenseID();
		HearingConfig->HearingRange = 2000.f;
		HearingConfig->DetectionByAffiliation.bDetectEnemies = true;
		HearingConfig->DetectionByAffiliation.bDetectFriendlies = true;
		HearingConfig->DetectionByAffiliation.bDetectNeutrals = true;

		AIPerComp->ConfigureSense(*HearingConfig);
		AIPerComp->SetDominantSense(HearingConfig->GetSenseImplementation());
	}
	AIPerComp->OnTargetPerceptionUpdated.AddDynamic(this, &AASAIController::On_Updated);

}

//ETeamAttitude::Type AASAIController::GetTeamAttitudeTowards(const AActor& Other) const
//{
//	return ETeamAttitude::Type();
//}


//���� ���� ��  
void AASAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn); //���ʹ��� �������� AIController�� ��� �� .
	RunAI();
}

