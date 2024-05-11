// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/ASEnemyCharacter.h"
#include "AI/ASAIController.h"
#include "DrawDebugHelpers.h"

AASEnemyCharacter::AASEnemyCharacter()
{
	AIControllerClass = AASAIController::StaticClass();
	
}

void AASEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	CheckShootingTarget();

}

bool AASEnemyCharacter::CheckShootingTarget()
{
	FHitResult OutHit;

	FVector Start = Gun->GetComponentLocation();
	FVector ForwardVector = GetActorForwardVector();
	FVector End = (Start + (ForwardVector * 1000.0f));

	FCollisionQueryParams CollisionParams;

	DrawDebugLine(GetWorld(), Start, End, FColor::Green, false, 1, 0, 1);
	bool isHit = GetWorld()->LineTraceSingleByChannel(OutHit, Start, End, ECC_GameTraceChannel2, CollisionParams);


	if (OutHit.GetActor() == AiRef->GetPlayer())
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("you are hitting: %s"),
			*OutHit.GetActor()->GetName()));
		return true;
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::Printf(TEXT("NO Target")));
		return false;
	}

	//AActor* Target = OutHit.GetActor();
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