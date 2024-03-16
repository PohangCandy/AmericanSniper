// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "ASGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ASPROTOTYPE_API UASGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	UASGameInstance();

	virtual void Init() override;
	
};
