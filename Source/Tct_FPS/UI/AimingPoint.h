// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AimingPoint.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class TCT_FPS_API UAimingPoint : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UImage* CenterPoint;
	/*UPROPERTY(Transient, meta = (BindWidgetAnim))
	TObjectPtr<UWidgetAnimation> PopUp;*/
	FTimerHandle TimerHandle_ResetColor;
	
public:
	void ChangeImageColorToRed();

	void ResetImageColor();

};
