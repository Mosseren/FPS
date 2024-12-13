// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tct_FPSGameMode.generated.h"

class AMyPlayerController;
class UEnhancedInputLocalPlayerSubsystem;
class UEnhancedInputComponent;

enum class ECountDownStatus
{
	Unstarted,
	Processing,
	TimeOver
};

UCLASS(minimalapi)
class ATct_FPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	int32 iImportantCnt;
	int32 iRoundTime;
	int32 TimeRemaining;

public:
	int32 iScore = 0;

	ECountDownStatus CountDownStatus;

	UEnhancedInputLocalPlayerSubsystem* EnhancedInputSubsystem;
	UEnhancedInputComponent* EnhancedInputComponent;

protected:
	ATct_FPSGameMode();

	FTimerHandle UpdateHandle;

	virtual void BeginPlay() override;

	void Tick(float DeltaTime);

	void UpdateHUDTime();

	void SelectImportantBoxes();

public:
	AMyPlayerController* PlayerController;

	void AddScore(int32 Value);

	void CoundDown();
};


