// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ASCharacterBase.generated.h"

UENUM()
enum class State
{
	None,
	Prone, //¾É±â
	Crawl, //¾þµå¸®±â
	Hurt,  //Àý¶Ò°Å¸®±â
	Hidden, //¼ûÀº »óÅÂ
	Dead
};

UCLASS()
class ASPROTOTYPE_API AASCharacterBase : public ACharacter
{
	GENERATED_BODY()

private:
	uint32 MaxHp;
	uint32 CurHp;
	uint8 Damage;
	State CurState;

public:
	// Sets default values for this character's properties
	AASCharacterBase();
	void SetDead();
	int GetHp();
	void SetHp(int Hp);
	void SetState(State NewState);
	State GetState();

protected:
	uint8 LowHp; // LowHp ÀÌÇÏ¸é Àý¶Ò°Å¸² 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> SearchMontage;

	FTimerHandle DeadTimerHandle;
};
