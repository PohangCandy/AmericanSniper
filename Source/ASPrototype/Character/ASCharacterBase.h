// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ASCharacterBase.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnStateChangeDelegate);

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
	uint32 MaxBulletNum;
	uint32 CurBulletNum;
	uint32 MaxMagazineNum;
	uint32 CurMagazineNum;
	uint32 MaxItemNum;
	uint32 CurItemNum;
	uint8 Damage;
	State CurState;
	//UPROPERTY()
	//class AASPlayerController* PlayerController;

public:
	// Sets default values for this character's properties
	AASCharacterBase();
	virtual void PostInitializeComponents() override;
	void SetDead();
	int GetHp();
	int GetBulletNum();
	int GetMagazineNum();
	int GetItemNum();
	float GetHpratio();
	void SetHp(int Hp);
	void SetBulletNum(int Num);
	void SetMagazineNum(int Num);
	void SetItem(int Num);
	void GetDamaged(int damage);
	void SetState(State NewState);
	State GetState();
	FOnStateChangeDelegate OnHpChanged;
	FOnStateChangeDelegate NumBulletChanged;
	FOnStateChangeDelegate NumMagazineChanged;
	FOnStateChangeDelegate NumItemChanged;


	UPROPERTY(VisibleAnywhere, Category = Stat)
	class UASCharacterStatComponent* CharacterStat;


protected:
	virtual void BeginPlay() override;

	uint8 LowHp; // LowHp ÀÌÇÏ¸é Àý¶Ò°Å¸² 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> SearchMontage;

	FTimerHandle DeadTimerHandle;
	//UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = Controller)
	//TSubclassOf<class AASPlayerController> CurplayerControllerClass;
};
