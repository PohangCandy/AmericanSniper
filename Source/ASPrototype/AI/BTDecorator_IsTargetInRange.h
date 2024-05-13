// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_IsTargetInRange.generated.h"

/**
 * 
 */
UCLASS()
class ASPROTOTYPE_API UBTDecorator_IsTargetInRange : public UBTDecorator
{
	GENERATED_BODY()
public:
	UBTDecorator_IsTargetInRange();
protected:
	float AttackRange;
};
