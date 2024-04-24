// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTDecorator_IsTargetInRange.h"
#include "ASAI.h"
#include "ASAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/ASEnemyBase.h"
#include "Character/ASCharacterPlayer.h" //플레이어와 에너미 사이 거리계산 때문에

UBTDecorator_IsTargetInRange::UBTDecorator_IsTargetInRange()
{
}

bool UBTDecorator_IsTargetInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	Super::CalculateRawConditionValue(OwnerComp, NodeMemory);
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AASEnemyBase* Enemy = Cast<AASEnemyBase>(ControllingPawn);
	AASAIController* AI = Cast<AASAIController>(ControllingPawn->GetController()); 
	float Distance;
	if (AI->PlayerRef!=nullptr)
	{
		Distance= Enemy->GetDistanceTo(AI->PlayerRef);
	}
	if (Distance <= AI->AttackRange)
	{	

		return true;
	}
	else
	{
		return false;
	}
}
