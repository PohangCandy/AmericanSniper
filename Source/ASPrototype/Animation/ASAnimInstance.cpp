// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ASAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UASAnimInstance::UASAnimInstance()
{
	MoveThreadshold = 3.0f;
	JumpeThreadshold = 30.0f;
}

void UASAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	Owner = Cast<ACharacter>(GetOwningActor());
	if (Owner)
	{
		Movement = Owner->GetCharacterMovement();
	}
}

void UASAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
	if (Movement)
	{
		GroundSpeed = Movement->Velocity.Size2D(); 
		bIsIdle = GroundSpeed < MoveThreadshold;

		bIsFalling = Movement->IsFalling();
		bIsJumping = bIsFalling & (Movement->Velocity.Z > JumpeThreadshold);

		bIsRunning = (Owner->GetCharacterMovement()->MaxWalkSpeed > 500) & !bIsIdle & !bIsJumping;
	}
}


