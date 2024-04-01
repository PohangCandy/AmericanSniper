// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Game/ASGameMode.h"
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

	virtual void OnPossess(APawn* aPawn) override;

	class UASMainGameWidget* GetHUDWidget();

	void ConnectUIwithData();

	class AActor* GetPlayerActor();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UASMainGameWidget> HUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UASMainGameWidget> SnipHUDWidgetClass;

	enum class EscreenMode
	{
		Basic,
		Sniping
	};

	void SetScreenMode(EscreenMode NewScreenMode);
	EscreenMode CurrentScreenMode = EscreenMode::Basic;
	void UIScreenChange();

private:
	UPROPERTY()
	class UASMainGameWidget* HUDWidget;

	UPROPERTY()
	class AActor* ControllerOwner;
};
