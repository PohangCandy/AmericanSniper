// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_Roaming.h"
#include "ASAIController.h"
EBTNodeResult::Type UBTTaskNode_Roaming::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AASAIController* AI = Cast<AASAIController>(ControllingPawn->GetController());

	switch (AI->Alertlvl)
	{
	case AlertLvl::Low:
		AI->SetBB_EnableRoaming(false);
		break;

	case AlertLvl::Medium:
		AI->SetBB_EnableRoaming(true);
		break;

	case AlertLvl::High:
		AI->SetBB_EnableRoaming(true);
		break;

	default:
		break;
	}
	
	return EBTNodeResult::Succeeded;
}
