// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ASEnemyCharacter.h"
#include "AI/ASAIController.h"


AASEnemyCharacter::AASEnemyCharacter()
{
	AIControllerClass = AASAIController::StaticClass();
}

void AASEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

}






//void AASEnemyCharacter::Move(const FInputActionValue& Value)
//{
//	FVector2D MovementVector = Value.Get<FVector2D>();
//
//	const FRotator Rotation = Controller->GetControlRotation();
//	const FRotator YawRotation(0, Rotation.Yaw, 0);
//
//	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
//	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
//
//	AddMovementInput(ForwardDirection, MovementVector.X);
//	AddMovementInput(RightDirection, MovementVector.Y);
//}
//
//void AASEnemyCharacter::Look(const FInputActionValue& Value)
//{
//	FVector2D LookAxisVector = Value.Get<FVector2D>();
//
//	AddControllerYawInput(LookAxisVector.X);
//	AddControllerPitchInput(LookAxisVector.Y);
//}
//
//void AASCharacterPlayer::SprintStart(const FInputActionValue& Value)
//{
//	GetCharacterMovement()->MaxWalkSpeed = 1000;
//}
//
//void AASCharacterPlayer::SprinEnd(const FInputActionValue& Value)
//{
//	GetCharacterMovement()->MaxWalkSpeed = 500;
//}