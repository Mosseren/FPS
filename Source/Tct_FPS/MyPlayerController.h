// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "MyPlayerController.generated.h"

class UHUDWidget;
class UAimingPoint;

UCLASS()
class TCT_FPS_API AMyPlayerController : public APlayerController
{
	GENERATED_BODY()
	
	TObjectPtr<UHUDWidget> HUDWidget;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UHUDWidget> HUDWidgetBlueprint;

	TObjectPtr<UAimingPoint> AimingPoint;
	UPROPERTY(EditAnywhere)
	TSubclassOf<UAimingPoint> AimingPointBlueprint;

	int32 BulletCount;
	int32 MaxBulletCount = 16;
public:
	AMyPlayerController();

	UFUNCTION()
	void BeginPlay();

	void InitializeHUD();

	void SetScore(const FString& Score);
	void SetTime(const FString& Time);
	
	void ConsumeBullet();

	void OnHitAnimAimingPoint();
};
