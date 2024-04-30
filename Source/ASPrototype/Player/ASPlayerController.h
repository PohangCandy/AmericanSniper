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

	void UIScreenChange();

protected:
	
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UASMainGameWidget> BasicHUDWidgetClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = UI)
	TSubclassOf<class UASMainGameWidget> SnipHUDWidgetClass;

	enum class EscreenMode
	{
		Basic,
		Sniping
	};

	void SetScreenMode(EscreenMode NewScreenMode);
	EscreenMode CurrentScreenMode = EscreenMode::Basic;
	//void UIScreenChange();

private:
	UPROPERTY()
	class UASMainGameWidget* CurMainHUDWidget;

	UPROPERTY()
	class AASCharacterBase* ControllerOwner;

	UPROPERTY()
	class UCameraComponent* SnipCam;

	UPROPERTY()
	USpringArmComponent* SnipSpringArm;

	UPROPERTY()
	AASCharacterBase* PlayerCharacter;

	UPROPERTY()
	class UCameraComponent* MainCam;

	UPROPERTY()
	class ACharacter* ControlCharacter;
};
