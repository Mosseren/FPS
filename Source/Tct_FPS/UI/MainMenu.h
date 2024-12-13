// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"

class UButton;
class UMyAssetManager;
/**
 * 
 */
UCLASS()
class TCT_FPS_API UMainMenu : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* LoginBtn;
	
public:
	UPROPERTY(EditDefaultsOnly, Category = "Level | 下一关路径")
	FName NextLevel = "FirstPersonMap";

	UFUNCTION()
	virtual void NativeOnInitialized() override;
	
	UFUNCTION()
	void OnLoginBtnClicked();
};
