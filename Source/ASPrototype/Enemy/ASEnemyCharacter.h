// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Enemy/ASEnemyBase.h"
#include "ASEnemyCharacter.generated.h"
/**
 * 
 */
UCLASS()
class ASPROTOTYPE_API AASEnemyCharacter : public AASEnemyBase
{
	GENERATED_BODY()
public:
	AASEnemyCharacter();

	virtual void Tick(float DeltaTime) override;
	bool CheckShootingTarget();

private:


protected:
	virtual void BeginPlay() override;
};
