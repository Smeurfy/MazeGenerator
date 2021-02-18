// Fill out your copyright notice in the Description page of Project Settings.


#include "TestWidget.h"

UTestWidget::UTestWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{

}

void UTestWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UTestWidget::UpdateComboCount(int value)
{
	if (TXTCombo && value > 1) 
	{
		if (TXTCombo->Visibility == ESlateVisibility::Hidden)
		{
			TXTCombo->SetVisibility(ESlateVisibility::Visible);
		}
		TXTCombo->SetText(FText::FromString(FString::FromInt(value) + "x combo"));

	}
}

void UTestWidget::ResetCombo()
{
	if (TXTCombo) 
	{
		TXTCombo->SetVisibility(ESlateVisibility::Hidden);
	}
}
