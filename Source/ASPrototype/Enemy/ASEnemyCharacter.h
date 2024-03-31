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

private:
	//void Move(const FInputActionValue& Value);
	//void Look(const FInputActionValue& Value);
	//void SprintStart(const FInputActionValue& Value);
	//void SprinEnd(const FInputActionValue& Value);

protected:
	virtual void BeginPlay() override;

};
