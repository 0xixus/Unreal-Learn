// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"

void UHUDWidget::SetHealthBarPercent(float NewPercent)
{
	if (NewPercent >= 0.0f && NewPercent <= 1.0f)
	{
		HealthBar->SetPercent(NewPercent);
	}
}

void 
UHUDWidget::SetMessageText(FString Message)
{
	FText MessageText = FText::FromString(Message);
	MessageTextBlock->SetText(MessageText);
}
