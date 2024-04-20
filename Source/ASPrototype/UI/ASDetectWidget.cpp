// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ASDetectWidget.h"
#include "Components/ProgressBar.h"
#include "Math/UnrealMathUtility.h"
//BB데이터 접근
#include "AI/ASAIController.h"
#include "Components/WidgetComponent.h"

UASDetectWidget::UASDetectWidget(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{

}

void UASDetectWidget::NativeConstruct()
{
	Super::NativeConstruct();
	DetectBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("DetectProgressBar")));
	ensure(DetectBar);

	DetectBar->SetVisibility(ESlateVisibility::Hidden);
}

void UASDetectWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	//timeline.TickTimeline(InDeltaTime);

	if (Owner!=nullptr) //이곳에 들어왔다는 건 AI의 Beginplay()가 호출됬음을 의미함 
	{	
		AiRef = Cast<AASAIController>(Owner);
		ensure(AiRef); //AI 객체 얻기 성공
		MaxPercent = AiRef->MaxLevel;
	}
}

void UASDetectWidget::IncreasePercent()
{	
	DetectBar->SetVisibility(ESlateVisibility::Visible);

	float value = 0.02f;
	AiRef->DetectionLevel = AiRef->DetectionLevel + value;
	CurPercent = FMath::Clamp(AiRef->DetectionLevel, 0.0f, MaxPercent);
	DetectBar->SetPercent(CurPercent);
	if (AiRef->DetectionLevel >= MaxPercent)
	{
		DetectBar->SetFillColorAndOpacity(FLinearColor::Red);
		return;
	}
}

void UASDetectWidget::DecreasePercent()
{
	float value = -0.01f;
	AiRef->DetectionLevel = AiRef->DetectionLevel + value;
	CurPercent = FMath::Clamp(AiRef->DetectionLevel, 0.0f, MaxPercent);
	DetectBar->SetPercent(CurPercent);
	if (AiRef->DetectionLevel <= 0.0f)
	{
		DetectBar->SetVisibility(ESlateVisibility::Hidden);
		return;
	}
}


void UASDetectWidget::SetAngle(float angle)
{
	SetRenderTransformAngle(angle);
}

