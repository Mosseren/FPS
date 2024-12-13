// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/LoadingScreen.h"
#include "LoadingScreen.h"
#include "Components/ProgressBar.h"

void ULoadingScreen::UpdateProgressBar(float Percent)
{
	FString DebugMessage = FString::Printf(TEXT("设置进度%f"), Percent);
	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, DebugMessage);

	ProgressBar->SetPercent(Percent);
}
