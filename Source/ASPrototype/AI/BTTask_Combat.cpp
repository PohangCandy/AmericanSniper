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
	//IsAttacking=false;
}

EBTNodeResult::Type UBTTask_Combat::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{	
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	Enemy = Cast<AASEnemyCharacter>(ControllingPawn);
	ensure(Enemy);
	AI = Cast<AASAIController>(Enemy->GetController());
	ensure(AI);

	if (Enemy==nullptr || AI==nullptr)
	{
		return EBTNodeResult::Failed;
	}
	
	Enemy->Attack();
	Enemy->CurState = EState::Attack;


	//IsAttacking = true;
	if (Enemy->CheckShootingTarget() == true)
	{
		AI->SetBB_CanShootTarget(true);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("CheckShootingTarget() == true")));
	}
	else
	{
		AI->SetBB_CanShootTarget(false);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString::Printf(TEXT("CheckShootingTarget() == false")));
	}

	Enemy->OnAttackEnd.AddLambda([this]()->void {Enemy->CurState = EState::Chasing; });


	//Enemy->CheckShootingTarget()==false 
	return EBTNodeResult::InProgress;

}



void UBTTask_Combat::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	Enemy = Cast<AASEnemyCharacter>(ControllingPawn);
	AI = Cast<AASAIController>(Enemy->GetController());
	ensure(AI);

	//Enemy->CheckShootingTarget();
	if (!(Enemy->CurState == EState::Attack))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
