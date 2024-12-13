// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "LoadingScreen.generated.h"

class UProgressBar;

UCLASS()
class TCT_FPS_API ULoadingScreen : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* ProgressBar;
	
	void UpdateProgressBar(float Percent);
};
