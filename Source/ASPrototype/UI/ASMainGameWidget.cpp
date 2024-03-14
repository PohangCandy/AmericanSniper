// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ASMainGameWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Player/ASPlayerState.h"
#include "Character/ASCharacterBase.h"

void UASMainGameWidget::BindPlayerBase(class AASCharacterBase* PlayerBase)
{
	CurrentPlayerBase = PlayerBase;
	CurrentPlayerBase->OnHpChanged.AddUObject(this, &UASMainGameWidget::UpdatePlayerState);
}

void UASMainGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	HpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HP")));
	BulletNum = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_LastBulletNum")));
	MagazineNum = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_LastMagazineNum")));
	ItemNum = Cast<UTextBlock>(GetWidgetFromName(TEXT("T_LastItem")));
}

void UASMainGameWidget::UpdatePlayerState()
{
	//HpBar->SetPercent(CurrentPlayerState->GetPlayerHpratio());
	HpBar->SetPercent(CurrentPlayerBase->GetHpratio());
}
