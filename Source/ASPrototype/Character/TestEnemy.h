// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "TestEnemy.generated.h"



UCLASS()
class ASPROTOTYPE_API ATestEnemy : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ATestEnemy();
	int damage = 10;
protected:
	//UFUNCTION()
	//virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;

};
