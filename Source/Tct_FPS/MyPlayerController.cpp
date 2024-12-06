// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "HUDWidget.h"
#include "Blueprint/UserWidget.h"


AMyPlayerController::AMyPlayerController()
{
}

void AMyPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void AMyPlayerController::InitializeHUD()
{
	if (HUDWidget == nullptr && HUDWidgetBlueprint != nullptr)
	{
		HUDWidget = CreateWidget<UHUDWidget>(this, HUDWidgetBlueprint);
		if (HUDWidget != nullptr)
		{
			HUDWidget->AddToViewport();
		}
	}
}

void AMyPlayerController::SetScore(const FString& Score)
{
	if (HUDWidget == nullptr)
	{
		InitializeHUD();
	}
	HUDWidget->SetScore(Score);
}

void AMyPlayerController::SetTime(const FString& Time)
{
	if (HUDWidget == nullptr)
	{
		InitializeHUD();
	}
	HUDWidget->SetTime(Time);
}
