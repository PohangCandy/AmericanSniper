// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_CheckForPlayer.h"
#include "ASAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/ASEnemyCharacter.h"

void UBTService_CheckForPlayer::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AASAIController* AI = Cast<AASAIController>(ControllingPawn->GetController());
	AASEnemyCharacter* Enemy = Cast<AASEnemyCharacter>(ControllingPawn);

	bool result = Enemy->CheckShootingTarget();
	if (Enemy->CurState==EState::Attack && !result)
	{
		AI->SetBB_CanShootTarget(false);
	}
	else
	{
		AI->SetBB_CanShootTarget(true);
	}
}
