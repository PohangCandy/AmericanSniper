// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_Combat.h"
#include "ASAIController.h"
#include "ASAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/ASEnemyCharacter.h"
#include "Animation/ASAIAnimInstance.h"

UBTTask_Combat::UBTTask_Combat()
{
	NodeName = TEXT("CombatSystem");
	bNotifyTick = true;
	IsAttacking=false;
}

EBTNodeResult::Type UBTTask_Combat::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{	
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AASEnemyBase* Enemy = Cast<AASEnemyBase>(ControllingPawn);
	ensure(Enemy);
	AASAIController* AI = Cast<AASAIController>(Enemy->GetController());
	ensure(AI);

	if (Enemy==nullptr || AI==nullptr)
	{
		return EBTNodeResult::Failed;
	}

	Enemy->Attack();
	IsAttacking = true;

	Enemy->OnAttackEnd.AddLambda([this]()->void {IsAttacking = false;});

	return EBTNodeResult::InProgress;
}

void UBTTask_Combat::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);
	if (!IsAttacking)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
