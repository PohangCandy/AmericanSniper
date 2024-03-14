// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ASPlayerController.h"
#include "UI/ASMainGameWidget.h"

AASPlayerController::AASPlayerController()
{
	static ConstructorHelpers::FClassFinder<UASMainGameWidget> UI_HUD_C(TEXT("/Game/UI/WB_GameBase_UI.WB_GameBase_UI_C"));
	//static ConstructorHelpers::FClassFinder<UASMainGameWidget> UI_HUD_C(TEXT("/Script/ASPrototype.ASMainGameWidget_C"));
	HUDWidgetClass = UI_HUD_C.Class;
}


void AASPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
	//SetInputMode(FInputModeGameAndUI());

	HUDWidget = CreateWidget<UASMainGameWidget>(this, HUDWidgetClass);
	HUDWidget->AddToViewport();
}

UASMainGameWidget* AASPlayerController::GetHUDWidget()
{
	return HUDWidget;
}


