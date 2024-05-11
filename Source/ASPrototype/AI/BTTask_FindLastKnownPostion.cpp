// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTask_FindLastKnownPostion.h"
#include "ASAIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Enemy/ASEnemyBase.h"
#include "Character/ASCharacterPlayer.h"

//�ǽɻ��°� �þ߷� �ĺ��� ���, LastKnownPosition = Recent Player��ġ 
//         ����� �ĺ��� ���, �̰��� �� ���� ��
EBTNodeResult::Type UBTTask_FindLastKnownPostion::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AASAIController* AI = Cast<AASAIController>(ControllingPawn->GetController());
	AI->SetBB_LastKnownPosition(AI->LastKnownPosition);
	// �ǽɻ��¿��� ������ �÷��̾� ��ġ������ �����Ǽ� ����, �߰��ٸ� �ʿ�(  )
	return EBTNodeResult::Succeeded;

}
