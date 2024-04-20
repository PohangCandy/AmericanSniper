// Fill out your copyright notice in the Description page of Project Settings.

#include "AI/BTService_StateManager.h"
#include "ASAI.h"
#include "ASAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/ASEnemyBase.h"

UBTService_StateManager::UBTService_StateManager()
{
	NodeName = TEXT("State_Manager");
	Interval = 0.5f;
}

void UBTService_StateManager::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{	
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AASAIController* AI = Cast<AASAIController>(ControllingPawn->GetController());
	AASEnemyBase* Enemy = Cast<AASEnemyBase>(ControllingPawn);
	if (AI->GetBB_IsDetect()==true)
	{
		Enemy->SetStateAnimation(EState::Chasing);
	}
	else 
	{
		Enemy->SetStateAnimation(EState::Idle);
	}
	
}


