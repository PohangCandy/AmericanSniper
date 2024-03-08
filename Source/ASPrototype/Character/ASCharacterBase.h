// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ASCharacterBase.generated.h"

UENUM()
enum class State
{
	None,
	Prone, //�ɱ�
	Crawl, //���帮��
	Hurt,  //���ҰŸ���
	Hidden, //���� ����
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
	uint8 LowHp; // LowHp ���ϸ� ���ҰŸ� 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> SearchMontage;

	FTimerHandle DeadTimerHandle;
};
