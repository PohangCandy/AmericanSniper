// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SoundSender.generated.h"

UCLASS()
class ASPROTOTYPE_API ASoundSender : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASoundSender();
	void NoiseCheck(FVector loc, TCHAR* tag);
	UPROPERTY()
	class AASEnemyCharacter* Enemy;
	class AASGameMode* GM;
	//void NoiseCheck(AActor* actor, TCHAR* tag);
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	class USoundBase* _sound;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	class AASCharacterPlayer* Player;
};
