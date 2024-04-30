// Fill out your copyright notice in the Description page of Project Settings.


#include "Player/ASPlayerController.h"
#include "Components/WidgetComponent.h"
#include "UI/ASMainGameWidget.h"
#include "Character/ASCharacterBase.h"


AASPlayerController::AASPlayerController()
{
	
	static ConstructorHelpers::FClassFinder<UASMainGameWidget> UI_HUD_C(TEXT("/Game/UI/WB_GameBase_UI.WB_GameBase_UI_C"));
	static ConstructorHelpers::FClassFinder<UASMainGameWidget> UI_Snip_C(TEXT("/Game/UI/WB_Sniping_UI.WB_Sniping_UI_C"));
	BasicHUDWidgetClass = UI_HUD_C.Class;
	SnipHUDWidgetClass = UI_Snip_C.Class;
	
}

void AASPlayerController::PostInitializeComponents()
{
	Super::PostInitializeComponents();
}

void AASPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	ControllerOwner = Cast<AASCharacterBase>(aPawn);
}


void AASPlayerController::BeginPlay()
{
	Super::BeginPlay();

	FInputModeGameOnly GameOnlyInputMode;
	SetInputMode(GameOnlyInputMode);
	//SetInputMode(FInputModeGameAndUI());

	CurMainHUDWidget = CreateWidget<UASMainGameWidget>(this, BasicHUDWidgetClass);
	//CurMainHUDWidget = CreateWidget<UASMainGameWidget>(this, SnipHUDWidgetClass);
	CurMainHUDWidget->AddToViewport();

	ConnectUIwithData();
	PlayerCharacter = Cast<AASCharacterBase>(GetCharacter());
	SnipSpringArm = Cast<USpringArmComponent>(GetCharacter()->GetDefaultSubobjectByName(TEXT("SnipSpringArm")));
	SnipCam = Cast<UCameraComponent>(GetCharacter()->GetDefaultSubobjectByName(TEXT("SnipCam")));
	MainCam = Cast<UCameraComponent>(GetCharacter()->GetDefaultSubobjectByName(TEXT("FollowCamera")));
}

UASMainGameWidget* AASPlayerController::GetHUDWidget()
{
	return CurMainHUDWidget;
}



void AASPlayerController::ConnectUIwithData()
{
	//auto CharacterWidget = Cast<UASMainGameWidget>(CurMainHUDWidget);
	//CharacterWidget->BindPlayerBase(Cast<AASCharacterBase>(ControllerOwner));
	//CharacterWidget->BindPlayerBaseForBullet(Cast<AASCharacterBase>(ControllerOwner));
	//CharacterWidget->BindPlayerBaseForMagazine(Cast<AASCharacterBase>(ControllerOwner));
	//CharacterWidget->BindPlayerBaseForItem(Cast<AASCharacterBase>(ControllerOwner));
	CurMainHUDWidget->BindPlayerBase(ControllerOwner);
	CurMainHUDWidget->BindPlayerBaseForBullet(ControllerOwner);
	CurMainHUDWidget->BindPlayerBaseForMagazine(ControllerOwner);
	CurMainHUDWidget->BindPlayerBaseForItem(ControllerOwner);
	CurMainHUDWidget->BindPlayerBaseForMagnification(ControllerOwner);
}

void AASPlayerController::SetScreenMode(EscreenMode NewScreenMode)
{
	CurrentScreenMode = NewScreenMode;
	switch (NewScreenMode)
	{
	case AASPlayerController::EscreenMode::Basic:
		CurMainHUDWidget->RemoveFromParent();
		CurMainHUDWidget = CreateWidget<UASMainGameWidget>(this, BasicHUDWidgetClass);
		ConnectUIwithData();
		CurMainHUDWidget->AddToViewport();
		ControllerOwner->InitUIData();
		
		break;
	case AASPlayerController::EscreenMode::Sniping:
		CurMainHUDWidget->RemoveFromParent();
		CurMainHUDWidget = CreateWidget<UASMainGameWidget>(this, SnipHUDWidgetClass);
		ConnectUIwithData();
		CurMainHUDWidget->AddToViewport();
		ControllerOwner->InitUIData();
		
		break;
	}
}



class AActor* AASPlayerController::GetPlayerActor()
{
	return ControllerOwner;
}

void AASPlayerController::UIScreenChange()
{
	switch (CurrentScreenMode)
	{
	case AASPlayerController::EscreenMode::Basic:
		SetScreenMode(EscreenMode::Sniping);
		//SetViewTarget(SnipCam);
		SnipCam->SetActive(true);
		SnipSpringArm->bUsePawnControlRotation = true;
		PlayerCharacter->bUseControllerRotationYaw = true;
		//bUseControllerRotationYaw = true;
		MainCam->SetActive(false);
		break;
	case AASPlayerController::EscreenMode::Sniping:
		SetScreenMode(EscreenMode::Basic);
		SnipCam->SetActive(false);
		MainCam->SetActive(true);
		PlayerCharacter->bUseControllerRotationYaw = false;
		break;
	}
}



