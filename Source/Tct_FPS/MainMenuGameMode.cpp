// Fill out your copyright notice in the Description page of Project Settings.



#include "MainMenuGameMode.h"
#include "UI/MainMenu.h"
#include "Blueprint/UserWidget.h"
#include "MyGameInstance.h"

void AMainMenuGameMode::BeginPlay()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (MyGameInstance)
	{
		MyGameInstance->CreateMainMenu();
	}
}
