// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ASMainGameWidget.generated.h"

/**
 * 
 */
UCLASS()
class ASPROTOTYPE_API UASMainGameWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	//void BindCharacterStat(class UASCharacterStatComponent* CharacterStat);
	//void BindPlayerState(class AASPlayerState);

protected:
	//virtual void NativeConstruct() override;
	//void UpdateCharacterStat();
	//void UpdatePlayerState();

private:
	TWeakObjectPtr<class UASCharacterStatComponent> CurrentCharacterStat;
	TWeakObjectPtr<class UASPlayerState> CurrentPlayerState;

	UPROPERTY()
	class UProgressBar* HpBar;

	UPROPERTY()
	class UTextBlock* BulletNum;

	UPROPERTY()
	class UTextBlock* MagazineNum;

	UPROPERTY()
	class UTextBlock* ItemNum;

};
