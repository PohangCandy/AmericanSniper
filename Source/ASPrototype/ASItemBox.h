// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Game/ASGameMode.h"
#include "GameFramework/Actor.h"
#include "ASItemBox.generated.h"

UCLASS()
class ASPROTOTYPE_API AASItemBox : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AASItemBox();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void PostInitializeComponents() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere, Category = Box)
	UBoxComponent* Trigger;

	UPROPERTY(VisibleAnywhere, Category = Box)
	UBoxComponent* ItemTrigger;


	UPROPERTY(VisibleAnywhere, Category = Box)
	UStaticMeshComponent* Box;

	UPROPERTY(VisibleAnywhere, Category = Effect)
	UParticleSystemComponent* Effect;

	void SetPlayerCanGripUI();

private:
	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedCom, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OutCharacterOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
	void OnScreenOverlap(UPrimitiveComponent* OverlappedCom, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	//void OnScreenOverlap(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);



	UFUNCTION()
	void OnEffectFinished(class UParticleSystemComponent* PSystem);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UDetectItemWidget> ItemWidgetClass;

	UPROPERTY()
	class UDetectItemWidget* ItemWidget;

private:
	APlayerController* PlayerController;

	bool canPlayerGrip;

public:
	bool GetPlayerCanGrip();
	void SetPlayerCanGrip(bool checkPlayerCanGrip);

	void OnTraceHit();
	void OutofTrace();

};
