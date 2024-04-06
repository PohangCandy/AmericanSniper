// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindPatrolLocation.h"
#include "ASAI.h"
#include "ASAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/ASEnemyBase.h"
//Enemy�� PatrolPath ��ü ĳ������ ����
#include "Enemy/PatrolPath.h"



UBTTask_FindPatrolLocation::UBTTask_FindPatrolLocation()
{
	//curIdx = 0;
	NodeName = TEXT("FindPatrolLocation");
}

EBTNodeResult::Type UBTTask_FindPatrolLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{	
	
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AASEnemyBase* Enemy = Cast<AASEnemyBase>(ControllingPawn);
	APatrolPath* PatrolpathActor = Cast<APatrolPath>(Enemy->PatrolPath);
	ensure(PatrolpathActor);
	AASAIController* AI = Cast<AASAIController>(ControllingPawn->GetController());
	int length;
	TArray<FVector> PArray =  PatrolpathActor->PatrolPoints;
	;

	length = PArray.Num()-1;
	if (PatrolpathActor->idx <= length)
	{	
		AI->SetBB_PathLoc(PArray[PatrolpathActor->idx]);
		PatrolpathActor->idx +=1;
	}
	else
	{
		PatrolpathActor->idx = 0;
	}
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("Name: %s || curIdx : %d "),*Enemy->Name, PatrolpathActor->idx));
	return EBTNodeResult::Succeeded;
}

//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT("curIdx : %d "), curIdx));