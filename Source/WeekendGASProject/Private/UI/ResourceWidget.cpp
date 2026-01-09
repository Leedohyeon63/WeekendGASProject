// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/ResourceWidget.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UResourceWidget::UpdateCurrent_Implementation(float InValue)
{
	Current->SetText(FText::AsNumber(FMath::RoundToInt(InValue)));
	CurrentValue = InValue;
	BAR->SetPercent(CurrentValue / MaxValue);
}

void UResourceWidget::UpdateMax_Implementation(float InValue)
{
	Max->SetText(FText::AsNumber(FMath::RoundToInt(InValue)));
	MaxValue = InValue;
	BAR->SetPercent(CurrentValue / MaxValue);
}

void UResourceWidget::SetWidgetColor(FLinearColor InColor)
{
	BAR->SetFillColorAndOpacity(InColor);
}
