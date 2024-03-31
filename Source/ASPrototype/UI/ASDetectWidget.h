// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "Blueprint/UserWidget.h"
#include "AI/ASAIController.h"
#include "ASDetectWidget.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FASDetectWidgetOnChangedSignature, bool b);

/**
 * 
 */


UCLASS()
class ASPROTOTYPE_API UASDetectWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UASDetectWidget(const FObjectInitializer& ObjectInitializer);
	void StartDetection();
	void StopDetection();
	void SetPercent(float NewPercent);
	UFUNCTION()
	void RunTimeline(float Value);
	void StartChasing(bool b);

	FASDetectWidgetOnChangedSignature OnChanged;

protected:
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UPROPERTY()
	TObjectPtr<class UProgressBar> DetectBar;

	FTimeline timeline;
	UPROPERTY(EditAnywhere,Category="Timeline")
	UCurveFloat* CurveFloat;


private:
	float CurPercent;
	float MaxPercent;
	float timeDeltaTime;
};
