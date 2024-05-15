// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/ASEnemyBase.h"
#include "Interface/ASAttackCheckInterface.h"
#include "ASEnemyCharacter.generated.h"
/**
 * 
 */
UCLASS()
class ASPROTOTYPE_API AASEnemyCharacter : public AASEnemyBase, public IASAttackCheckInterface
{
	GENERATED_BODY()
public:
	AASEnemyCharacter();

	bool AttackCheck();
	float TakeDamage(float DamageAmount, FHitResult HitResult , AActor* DamageCauser);
	virtual void Tick(float DeltaTime) override;

private:


protected:
	virtual void BeginPlay() override;
};
