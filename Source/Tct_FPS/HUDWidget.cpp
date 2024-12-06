// Fill out your copyright notice in the Description page of Project Settings.


#include "HUDWidget.h"
#include "Components/TextBlock.h"

void UHUDWidget::SetScore(const FString& Score)
{
	if (ScoreText)
	{
		ScoreText->SetText(FText::FromString(Score));
	}
}

void UHUDWidget::SetTime(const FString& Time)
{
	if (TimeText)
	{
		TimeText->SetText(FText::FromString(Time));
	}
}
