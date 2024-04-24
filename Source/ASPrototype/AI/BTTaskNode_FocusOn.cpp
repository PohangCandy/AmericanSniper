// Fill out your copyright notice in the Description page of Project Settings.


#include "AI/BTTaskNode_FocusOn.h"
#include "ASAIController.h"
#include "Character/ASCharacterPlayer.h"
#include "Enemy/ASEnemyBase.h"
#include "Kismet/KismetMathLibrary.h"
#include "Math/UnrealMathUtility.h"

EBTNodeResult::Type UBTTaskNode_FocusOn::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{


	APawn* ControllingPawn = OwnerComp.GetAIOwner()->GetPawn();
	AASAIController* AI = Cast<AASAIController>(ControllingPawn->GetController());
	AASEnemyBase* Enemy = Cast<AASEnemyBase>(ControllingPawn);
	AASCharacterPlayer* Player = Cast<AASCharacterPlayer>(AI->PlayerRef); ensure(Player);
	if (Player != nullptr)
	{
		//if (GetBB_IsDetect()) { SetFocus(player); }
		FRotator EnemyRotation = Enemy->GetActorRotation();
		FVector EnemyLocation = Enemy->GetActorLocation();
		FVector PlayerLocation = Player->GetActorLocation();
		FRotator RotationDifferenceValue = UKismetMathLibrary::FindLookAtRotation(EnemyLocation, PlayerLocation);
		FRotator ResultValue = FRotator(0.0f, RotationDifferenceValue.Yaw ,0.0f);
		FRotator RotatorValue = FMath::RInterpTo(EnemyRotation, ResultValue,GetWorld()->GetDeltaSeconds(),0.0f);
		Enemy->SetActorRotation(RotatorValue);
		//AI->SetFocus(Player);
		//GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Red, FString::Printf(TEXT(" SetFocus ")));
		return EBTNodeResult::Succeeded;
	}
	else
	{
		return EBTNodeResult::Failed;
	}
}
