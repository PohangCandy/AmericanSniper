// Fill out your copyright notice in the Description page of Project Settings.


#include "Animation/ASAnimInstance.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UASAnimInstance::UASAnimInstance()
{
	MoveThreadshold = 3.0f;
	JumpeThreadshold = 30.0f;
}

void UASAnimInstance::StateHandler(State NewState)
{
	switch (NewState)
	{
	case State::None:
		break;
	case State::Prone:
		break;
	case State::Crawl:
		break;
	case State::Hurt:
		//bIsHurt=true; //Null의 내부 변수를 참조해서 에러 발생
		UE_LOG(LogTemp, Log, TEXT("HURT"));
		//절뚝거림 구현
	case State::Hidden:
		break;
	case State::Dead:
		break;
	default:
		break;
	}
}

//임시 함수
//void UASAnimInstance::SetCurrentHp(int NewHp)
//{
//	Hp = NewHp;
//}

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

		//bIsHurt = Hp < 50;
	}
}


