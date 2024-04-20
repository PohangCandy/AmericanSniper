// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTService_UpdateLastKnownPostion.h"
#include "ASAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/ASEnemyBase.h"
#include "Character/ASCharacterPlayer.h"
 


UBTService_UpdateLastKnownPostion::UBTService_UpdateLastKnownPostion()
{
	NodeName = TEXT("UpdateLastKnownPostion_Manager");
	Interval = 0.5f;
}

void UBTService_UpdateLastKnownPostion::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AASAIController* AI = Cast<AASAIController>(ControllingPawn->GetController());
	AASCharacterPlayer* Player = Cast<AASCharacterPlayer>(AI->PlayerRef);
	AI->SetBB_LastKnownPosition(Player->GetActorLocation());
}

