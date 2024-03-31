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
#include "UI/ASDetectWidget.h"
#include "Components/WidgetComponent.h"

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
	//UASDetectWidget* DetectWidget = Cast<UASDetectWidget>(Widget); 
	ensure(player);
	AASEnemyCharacter* Enemy = Cast<AASEnemyCharacter>(GetPawn());
	ensure(Enemy);
	UASDetectWidget* DetectWidget = Cast<UASDetectWidget>(Enemy->GetWidget()->GetUserWidgetObject());
	ensure(DetectWidget);
	if (GetBlackboardComponent()->GetValueAsObject(BBKEY_TARGET)->IsValidLowLevel())
	{
		GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, nullptr); //나가야 하는 상황 
		//SetDetectState(false); 
		DetectWidget->StopDetection();
	}
	else
	{
		GetBlackboardComponent()->SetValueAsObject(BBKEY_TARGET, player); //들어가야 하는 상황 
		//SetDetectState(true);
		DetectWidget->StartDetection();
	}
}

void AASAIController::SetDetectState(bool b)
{	
	GetBlackboardComponent()->SetValueAsBool(BBKEY_IsDetect, b);
}

bool AASAIController::GetDetectState()
{	
	return GetBlackboardComponent()->GetValueAsBool(BBKEY_IsDetect);
}


void AASAIController::OnPawnDetected(const TArray<AActor*>& DetectedPawns)
{	
	for (int32 i = 0; i < DetectedPawns.Num(); ++i)
	{
		AASCharacterPlayer* DetectedPawn = Cast<AASCharacterPlayer>(DetectedPawns[i]);
		CheckPlayer(DetectedPawn);
	}
}

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


//빙의 시작 시  
void AASAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn); //에너미의 소유권은 AIController가 얻게 됨 .
	RunAI();

	// 월드의 타이머 매니저에 콜백을 등록
	// GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &AASAIController::RunAI(), 3.f, true);

}
