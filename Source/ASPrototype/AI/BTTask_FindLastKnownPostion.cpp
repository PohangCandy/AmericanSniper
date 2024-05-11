// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindLastKnownPostion.h"
#include "ASAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/ASEnemyBase.h"
#include "Character/ASCharacterPlayer.h"

//의심상태가 시야로 식별된 경우, LastKnownPosition = Recent Player위치 
//         사운드로 식별된 경우, 이곳에 안 들어가도 됨
EBTNodeResult::Type UBTTask_FindLastKnownPostion::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AASAIController* AI = Cast<AASAIController>(ControllingPawn->GetController());
	AI->SetBB_LastKnownPosition(AI->LastKnownPosition);
	// 의심상태에서 무조건 플레이어 위치값으로 수정되서 문제, 중간다리 필요(  )
	return EBTNodeResult::Succeeded;

}
