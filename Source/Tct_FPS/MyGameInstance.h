// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyAssetManager.h"
#include "MyGameInstance.generated.h"

class UMyAssetManager;
class ULoadingScreen;
class UMainMenu;

UCLASS()
class TCT_FPS_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	//UMyAssetManager* MyAssetManager;
	//FSoftObjectPath TargetPath;
	//FTimerHandle UpdateProgressTimer;

public:
	/*UPROPERTY(EditDefaultsOnly, Category = "UI | 加载")
	TSubclassOf<ULoadingScreen> LoadingScreenBlueprint;
	TObjectPtr<ULoadingScreen> LoadingScreen;*/

	UPROPERTY(EditDefaultsOnly, Category = "UI | 主菜单")
	TSubclassOf<UMainMenu> MainMenuBluePrint;
	TObjectPtr<UMainMenu> MainMenuWidget;

	void CreateMainMenu();

	void HideMainMenu();

	//void MyAsyncLoadLevel(FSoftObjectPath Path);

	//FOnPackageLoaded OnLoadCompleteDelegate;
	//void OnLoadComplete();

	//void UpdateLoadingScreenProgress();
};
