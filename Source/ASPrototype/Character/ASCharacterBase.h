// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ASCharacterBase.generated.h"

UCLASS()
class ASPROTOTYPE_API AASCharacterBase : public ACharacter
{
	GENERATED_BODY()
	uint32 MaxHp;
	uint32 CurHp;
public:
	// Sets default values for this character's properties
	AASCharacterBase();
	void SetDead();
	int GetHp();
	void SetHp(int Hp);
protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> SearchMontage;

	FTimerHandle DeadTimerHandle;
};
