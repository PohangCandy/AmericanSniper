// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ASPlayerController.h"
#include "Components/WidgetComponent.h"
#include "UI/ASMainGameWidget.h"
#include "Character/ASCharacterBase.h"


AASPlayerController::AASPlayerController()
{
	static ConstructorHelpers::FClassFinder<UASMainGameWidget> UI_HUD_C(TEXT("/Game/UI/WB_GameBase_UI.WB_GameBase_UI_C"));
	//static ConstructorHelpers::FClassFinder<UASMainGameWidget> UI_HUD_C(TEXT("/Script/ASPrototype.ASMainGameWidget_C"));
	HUDWidgetClass = UI_HUD_C.Class;
}

void AASPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AASPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	ControllerOwner = aPawn;
}


void AASPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
	//SetInputMode(FInputModeGameAndUI());

	HUDWidget = CreateWidget<UASMainGameWidget>(this, HUDWidgetClass);
	HUDWidget->AddToViewport();

	ConnectUIwithData();
}

UASMainGameWidget* AASPlayerController::GetHUDWidget()
{
	return HUDWidget;
}



void AASPlayerController::ConnectUIwithData()
{
	auto CharacterWidget = Cast<UASMainGameWidget>(HUDWidget);
	CharacterWidget->BindPlayerBase(Cast<AASCharacterBase>(ControllerOwner));
	CharacterWidget->BindPlayerBaseForBullet(Cast<AASCharacterBase>(ControllerOwner));

}


