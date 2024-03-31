// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ASEnemyBase.generated.h"

UENUM()
enum class EState
{
	None,
	Attack, //돌격상태 
	Hurt,  //절뚝거리기
	Hidden, //숨은 상태
	Dead
};


UCLASS()
class ASPROTOTYPE_API AASEnemyBase : public ACharacter
{
	GENERATED_BODY()
public:
	// Sets default values for this character's properties
	AASEnemyBase();

private:
	uint32 MaxHp;
	uint32 CurHp;
	uint8 Damage;
	EState CurState;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Animation)
	TObjectPtr<class UAnimMontage> DeadMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Weapon)
	TObjectPtr<class UStaticMeshComponent> Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Widget)
	TObjectPtr<class UWidgetComponent> DetectBar;

	void SetState(EState NewState);
	EState GetState();


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	void SetStateAnimation(EState NewState);

	class UWidgetComponent* GetWidget();
};

