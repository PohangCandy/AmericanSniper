// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "Character/ASCharacterBase.h" //의존
#include "ASAnimInstance.generated.h"
/**
 * 
 */
UCLASS()
class ASPROTOTYPE_API UASAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UASAnimInstance();
	State state;
	void StateHandler(State NewState);
	//void SetCurrentHp(int NewHp);
	//int Hp = 100;

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class ACharacter> Owner; //Animinstance를 사용하고 있는 케릭터에 대한 정보 

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Character)
	TObjectPtr<class UCharacterMovementComponent> Movement;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsIdle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float GroundSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float MoveThreadshold; //임계값 (특정수치가 올라가면 움직임)

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsRunning : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsJumping : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsFalling : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	uint8 bIsHurt : 1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Character)
	float JumpeThreadshold;

};
