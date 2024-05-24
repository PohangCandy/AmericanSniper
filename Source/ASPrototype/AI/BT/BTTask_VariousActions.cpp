// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT/BTTask_VariousActions.h"
#include "AI/ASAIController.h"
#include "AI/ASAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/ASEnemyCharacter.h"

EBTNodeResult::Type UBTTask_VariousActions::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	Enemy = Cast<AASEnemyCharacter>(ControllingPawn);
	AI = Cast<AASAIController>(Enemy->GetController());

	Enemy->PlayReloadAnimation();
	IsPlaying = true;
	Enemy->OnReloadEnd.AddLambda([this]()->void {IsPlaying = false; });
	return EBTNodeResult::InProgress;
}

void UBTTask_VariousActions::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!(IsPlaying))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
