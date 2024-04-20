// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
/*#include "Components/TimelineComponent.h" *///제거하시오
#include "Blueprint/UserWidget.h"
#include "AI/ASAIController.h"
#include "ASDetectWidget.generated.h"

//DECLARE_MULTICAST_DELEGATE_OneParam(FUASDetectWidgetOnChangedSignature, bool b)
/**
 * 
 */


UCLASS()
class ASPROTOTYPE_API UASDetectWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	UASDetectWidget(const FObjectInitializer& ObjectInitializer);
	void IncreasePercent();
	void DecreasePercent();

	UFUNCTION()
	/*void RunTimeline(float Value);*/
	//void StartChasing(bool b);

	void SetAngle(float angle);

	FORCEINLINE AActor* GetOwner() { return Owner; }
	FORCEINLINE void SetOwner(AActor* newOwner) { Owner = newOwner; }

	float CurPercent;
	float MaxPercent;
	bool DetectOn;

protected:
	AActor* Owner;

	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime);

	UPROPERTY()
	TObjectPtr<class UProgressBar> DetectBar;

	//FTimeline timeline;
	//UPROPERTY(EditAnywhere,Category="Timeline")
	//UCurveFloat* CurveFloat;


private:
	class AASAIController* AiRef;

};
