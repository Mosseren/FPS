// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Tct_FPSGameMode.generated.h"

UCLASS(minimalapi)
class ATct_FPSGameMode : public AGameModeBase
{
	GENERATED_BODY()

protected:
	bool bTimeOver = false;
	int32 iImportantCnt;
	int32 iRoundTime;

public:
	int32 iScore = 0;

protected:
	ATct_FPSGameMode();

	FTimerHandle TimerHandle;

	void SetTimer();

	virtual void BeginPlay() override;

	void Tick(float DeltaTime);

	void OnTimerComplete();

	void SelectImportantBoxes();

public:
	void AddScore(int32 Value);
};


