// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ASPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class ASPROTOTYPE_API AASPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public: 
	AASPlayerController();

	virtual void PostInitializeComponents() override;

	class UASMainGameWidget* GetHUDWidget();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UASMainGameWidget> HUDWidgetClass;

private:
	UPROPERTY()
	class UASMainGameWidget* HUDWidget;
};
