// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerController.h"
#include "HUDWidget.h"
#include "Blueprint/UserWidget.h"
#include "UI/AimingPoint.h"


AMyPlayerController::AMyPlayerController()
{
	BulletCount = MaxBulletCount;
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
			HUDWidget->SetBulletCount(BulletCount);
		}
	}
	if (!AimingPoint && AimingPointBlueprint)
	{
		AimingPoint = CreateWidget<UAimingPoint>(this, AimingPointBlueprint);
		AimingPoint->AddToViewport();
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

void AMyPlayerController::ConsumeBullet()
{
	BulletCount -= 1;
	if (BulletCount == 0)
	{
		BulletCount = MaxBulletCount;
	}
	HUDWidget->SetBulletCount(BulletCount);
}

void AMyPlayerController::OnHitAnimAimingPoint()
{
	if (AimingPoint)
	{
		AimingPoint->ChangeImageColorToRed();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, TEXT("AimingPoint null"));
	}
}
