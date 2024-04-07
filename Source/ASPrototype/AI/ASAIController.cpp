// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/ASAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "ASAI.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Enemy/ASEnemyCharacter.h"
#include "Character/ASCharacterPlayer.h"

#include "Kismet/KismetMathLibrary.h" //charactor의 움직임 

//탐지 위젯 추가
#include "Components/WidgetComponent.h"
#include "UI/ASDetectWidget.h"



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


	//Widget Component Setting 
	DetectBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("DetectWidget"));
	static ConstructorHelpers::FClassFinder<UUserWidget> DetectBarRef(TEXT("/Game/UI/WB_DetectBar_UI.WB_DetectBar_UI_C"));
	if (DetectBarRef.Class)
	{
		DetectBar->SetWidgetClass(DetectBarRef.Class);
		DetectBar->SetWidgetSpace(EWidgetSpace::Screen);
		DetectBar->SetDrawSize(FVector2D(150.0f, 15.0f));
		DetectBar->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}

	//생성자에서만 Casting 안됨 
	//TSubclassOf<UUserWidget> WidgetObject = DetectBar->GetWidgetClass();
	//UASDetectWidget* uiRef = Cast<UASDetectWidget>(WidgetObject);
	//ensure(UiRef);
	//UiRef->SetOwner(this);

	//ID 세팅 
	//AASEnemyBase* EnemyRef = Cast<AASEnemyBase>(GetPawn());
	//if (EnemyRef)
	//{
	//	TeamId = FGenericTeamId(EnemyRef->ID);
	//}
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
	
	//임시 : 오직 플레이어만 인식 (적끼리 인식X)
	if (player==NULL){return;}
	Pass = true;

	//UiRef->OnChanged.AddUObject(this, &AASAIController::SetBB_IsDetect);
	UiRef->AddToViewport();

	if (GetBB_Target()->IsValidLowLevel())
	{
		SetBB_Target(nullptr); //나가야 하는 상황 
		UiRef->StopDetection();
	}
	else
	{
		SetBB_Target(player); //들어가야 하는 상황
		UiRef->StartDetection();
	}
}


//BB 데이터 접근 
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



void AASAIController::OnPawnDetected(const TArray<AActor*>& DetectedPawns) //적 둘이 마주보면 문제 발생 
{	
	for (int32 i = 0; i < DetectedPawns.Num(); ++i)
	{
		PlayerRef = Cast<AASCharacterPlayer>(DetectedPawns[i]);
		ensure(DetectedPawns[i]);
		CheckPlayer(PlayerRef);
	}
}

void AASAIController::Tick(float DeltaTime)
{	
	if (Pass) // 시작 시 바로 들어오는 거 방지
	{
		if (PlayerRef!=nullptr) //StartDetection() 호출 시 -> 동작   ,   StopDetection() 호출 후 UI 사라지면 -> 정지
		{


			//UI 위치 조정
			FRotator ControlRotator = GetControlRotation();
			FVector PlayerLoc = PlayerRef->GetActorLocation(); 
			FVector EnemyLoc = EnemyRef->GetActorLocation();
			FRotator ControllerRotator = UGameplayStatics::GetPlayerController(GetWorld(), 0)->GetControlRotation();
			FRotator IntervalRotator = UKismetMathLibrary::FindLookAtRotation(PlayerLoc, EnemyLoc);
			FRotator AngleRotator = UKismetMathLibrary::NormalizedDeltaRotator(IntervalRotator, ControllerRotator);
			float Angle = AngleRotator.Yaw;
			UiRef->SetAngle(Angle);

		}

	}
}

void AASAIController::BeginPlay()
{
	Super::BeginPlay();
	UiRef = Cast<UASDetectWidget>(DetectBar->GetUserWidgetObject());
	ensure(UiRef);
	UiRef->SetOwner(this);
	EnemyRef = Cast<AASEnemyCharacter>(GetPawn());
	ensure(EnemyRef);

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

//AASAIController* AASAIController::ReturnAIRef(AASAIController* ref)
//{
//	AIOnChanged.Broadcast(ref);
//	return this;
//}

void AASAIController::SetupPerception()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	if (SightConfig)
	{
		SetPerceptionComponent(*CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("Perception Component")));

		SightConfig->SightRadius = 500.f;
		SightConfig->LoseSightRadius = SightConfig->SightRadius + 25.f;
		SightConfig->PeripheralVisionAngleDegrees = 60.f;
		SightConfig->DetectionByAffiliation.bDetectEnemies = true;
		SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
		SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

		GetPerceptionComponent()->SetDominantSense(*SightConfig->GetSenseImplementation());
		GetPerceptionComponent()->OnPerceptionUpdated.AddDynamic(this, &AASAIController::OnPawnDetected);
		GetPerceptionComponent()->ConfigureSense(*SightConfig);
	}
}

//ETeamAttitude::Type AASAIController::GetTeamAttitudeTowards(const AActor& Other) const
//{
//	return ETeamAttitude::Type();
//}


//빙의 시작 시  
void AASAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn); //에너미의 소유권은 AIController가 얻게 됨 .
	RunAI();
}