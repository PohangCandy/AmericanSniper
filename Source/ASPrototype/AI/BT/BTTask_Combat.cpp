// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BT/BTTask_Combat.h"
#include "AI/ASAIController.h"
#include "AI/ASAI.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/ASEnemyCharacter.h"
#include "Animation/ASAIAnimInstance.h"

UBTTask_Combat::UBTTask_Combat()
{
	NodeName = TEXT("CombatSystem");
	bNotifyTick = true;
	IsPlaying =false;
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
	IsPlaying = true;


	//Test
	if (Enemy->AttackCheck() == true)
	{
		AI->SetBB_CanShootTarget(true);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, FString::Printf(TEXT("CheckShootingTarget() == true")));
	}
	else
	{
		AI->SetBB_CanShootTarget(false);
		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString::Printf(TEXT("CheckShootingTarget() == false")));
	}

	Enemy->OnAttackEnd.AddLambda([this]()->void {IsPlaying = false;});

	return EBTNodeResult::InProgress;

}



void UBTTask_Combat::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	Enemy = Cast<AASEnemyCharacter>(ControllingPawn);
	AI = Cast<AASAIController>(Enemy->GetController());
	ensure(AI);

	if (IsPlaying)
	{	
		//true가 한번이라도 나왔다면 그대로 공격하겠다. 와리가리 방지
		bool result = Enemy->AttackCheck();
		if (result){ AI->SetBB_CanShootTarget(result); }
	}
	else
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	}
}
