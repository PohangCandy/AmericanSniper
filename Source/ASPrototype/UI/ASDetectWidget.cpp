// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ASDetectWidget.h"
#include "Components/ProgressBar.h"
#include "Math/UnrealMathUtility.h"
//BB데이터 접근
#include "Enemy/ASEnemyBase.h"
#include "AI/ASAIController.h"

UASDetectWidget::UASDetectWidget(const FObjectInitializer& ObjectInitializer) :Super(ObjectInitializer)
{
	CurPercent = 0.0f;
	MaxPercent = 1.0f;
}

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
}

void UASDetectWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	timeline.TickTimeline(InDeltaTime);
}

void UASDetectWidget::SetPercent(float NewPercent)
{
	DetectBar->SetPercent(NewPercent);
}

void UASDetectWidget::StartDetection()
{	
	timeline.Play();
	DetectBar->SetVisibility(ESlateVisibility::Visible);
}

void UASDetectWidget::StopDetection()
{		
	timeline.Reverse();
}


void UASDetectWidget::RunTimeline(float Value) 
{
	//BB정보 얻기위해 캐스팅  (Player가 아닌 Enemy 얻어오기) 
	/*APlayerController* PlayerController = 
	APawn* pawn= Cast<APawn>(PlayerController->GetPawn());
	ensure(pawn);
	AASEnemyBase* enemyRef = Cast<AASEnemyBase>(pawn);
	ensure(enemyRef);
	AASAIController* AiControllerRef = Cast<AASAIController>(pawn->GetOwner());
	ensure(AiControllerRef);*/

	//Setting ProgressBar 
	float NewPercent = FMath::Lerp(0.0f, MaxPercent, Value);
	CurPercent = FMath::Clamp(NewPercent, 0.0f, MaxPercent);
	DetectBar->SetPercent(CurPercent);

	//ProgressBar limit
	if (CurPercent >= MaxPercent)
	{	
		DetectBar->SetFillColorAndOpacity(FLinearColor::Red); //Change Color Red 
		//AiControllerRef->SetDetectState(true)
		StartChasing(true);
	}
	else if(!timeline.IsPlaying())
	{	
		DetectBar->SetFillColorAndOpacity(FLinearColor::White);
		DetectBar->SetVisibility(ESlateVisibility::Hidden);
		//AiControllerRef->SetDetectState(false);
		StartChasing(false);
	}
	GEngine->AddOnScreenDebugMessage(-1, 2.0f, FColor::Black, FString::Printf(TEXT("CurPercent : %f"), CurPercent));
}

void UASDetectWidget::StartChasing(bool b)
{
	OnChanged.Broadcast(b);
}



//if (timeDeltaTime > 1.0f)
//{
//	GetWorldTimerManager().ClearTimer(fTimeHandler);
//}

//		GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Black, FString::Printf(TEXT("when CurPercent : %f , STOP1 "), CurPercent));