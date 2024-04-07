// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ASDetectWidget.h"
#include "Components/ProgressBar.h"
#include "Math/UnrealMathUtility.h"
//BB데이터 접근
#include "AI/ASAIController.h"
#include "Components/WidgetComponent.h"

UASDetectWidget::UASDetectWidget(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	CurPercent = 0.0f;
	MaxPercent = 1.0f;
	
}

//AASAIController* UASDetectWidget::GetAIRef(AASAIController* ref)
//{
//	return ref;
//}

void UASDetectWidget::NativeConstruct()
{
	Super::NativeConstruct();
	DetectBar = Cast<UProgressBar>(GetWidgetFromName(TEXT("DetectProgressBar")));
	ensure(DetectBar);

	if (CurveFloat)
	{
		FOnTimelineFloat BindTimeline;
		BindTimeline.BindUFunction(this, FName("RunTimeline"));
		timeline.AddInterpFloat(CurveFloat, BindTimeline);
		timeline.SetLooping(false);
	}
	DetectBar->SetVisibility(ESlateVisibility::Hidden);
	
	//UWidgetComponent* WCref = Cast<UWidgetComponent>(this);  	ensure(WCref);
	//AASAIController* aiRef = Cast<AASAIController>GetOwner());
	//ensure(aiRef);

}

void UASDetectWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	timeline.TickTimeline(InDeltaTime);
	if (Owner!=nullptr)
	{
		AASAIController* AIController = Cast<AASAIController>(Owner);
		ensure(AIController); //AI 객체 얻기
	}
}

void UASDetectWidget::SetPercent(float NewPercent)
{
	DetectBar->SetPercent(NewPercent);
}

void UASDetectWidget::StartDetection()
{	
	//StartChasing(true);
	timeline.Play();
	DetectBar->SetVisibility(ESlateVisibility::Visible);
}

void UASDetectWidget::StopDetection()
{		
	timeline.Reverse();
}


void UASDetectWidget::RunTimeline(float Value) 
{

	//Setting ProgressBar 
	float NewPercent = FMath::Lerp(0.0f, MaxPercent, Value);
	CurPercent = FMath::Clamp(NewPercent, 0.0f, MaxPercent);
	DetectBar->SetPercent(CurPercent);

	//ProgressBar limit
	if (CurPercent >= MaxPercent)
	{	
		DetectBar->SetFillColorAndOpacity(FLinearColor::Red); //Change Color Red 

	}
	else if(!timeline.IsPlaying())
	{	
		DetectBar->SetFillColorAndOpacity(FLinearColor::White);
		DetectBar->SetVisibility(ESlateVisibility::Hidden);
		//StartChasing(false);
	}
	//GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, FString::Printf(TEXT("CurPercent : %f"), CurPercent));
}

//void UASDetectWidget::StartChasing(bool b)
//{
//	OnChanged.Broadcast(b);
//}


void UASDetectWidget::SetAngle(float angle)
{
	SetRenderTransformAngle(angle);
}



//if (timeDeltaTime > 1.0f)
//{
//	GetWorldTimerManager().ClearTimer(fTimeHandler);
//}

//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString::Printf(TEXT("when CurPercent : %f , STOP1 "), CurPercent));