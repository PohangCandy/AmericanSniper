// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/DetectItemWidget.h"
#include "Components/EditableTextBox.h"
#include "Components/TextBlock.h"

void UDetectItemWidget::NativeConstruct()
{
	PressButtonText = Cast<UEditableTextBox>(GetWidgetFromName(TEXT("TB_ButtonName")));
	ItemName = Cast<UTextBlock>(GetWidgetFromName(TEXT("Txt_ItemName")));
}
