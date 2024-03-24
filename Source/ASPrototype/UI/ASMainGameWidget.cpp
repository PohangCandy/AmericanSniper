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

void UASMainGameWidget::BindPlayerBaseForBullet(AASCharacterBase* PlayerBase)
{
	CurrentPlayerBase = PlayerBase;
	CurrentPlayerBase->NumBulletChanged.AddUObject(this, &UASMainGameWidget::UpdateBulletUI);
}


void UASMainGameWidget::NativeConstruct()
{
	Super::NativeConstruct();
	BulletNumUI = Cast<UTextBlock>(GetWidgetFromName(TEXT("LastBulletNum")));
	HpBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("PB_HP")));
	MagazineNum = Cast<UTextBlock>(GetWidgetFromName(TEXT("TB_LastMagazineNum")));
	//ItemNum = Cast<UTextBlock>(GetWidgetFromName(TEXT("T_LastItem")));
}

void UASMainGameWidget::UpdatePlayerState()
{
	//HpBar->SetPercent(CurrentPlayerState->GetPlayerHpratio());
	HpBar->SetPercent(CurrentPlayerBase->GetHpratio());
}

void UASMainGameWidget::UpdateBulletUI()
{
	BulletNumUI->SetText(FText::FromString(FString::FromInt(CurrentPlayerBase->GetBulletNum())));
}

