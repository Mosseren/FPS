// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameInstance.h"
#include "Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "UI/LoadingScreen.h"
#include "UI/MainMenu.h"


void UMyGameInstance::CreateMainMenu()
{
	//OnLoadCompleteDelegate.BindUFunction(this, "OnLoadComplete");
	// 主菜单则创建UI
	if (!MainMenuWidget && MainMenuBluePrint)
	{
		MainMenuWidget = CreateWidget<UMainMenu>(this, MainMenuBluePrint);

	}
	MainMenuWidget->AddToViewport();
	// 呼出鼠标
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = true;
		FInputModeUIOnly InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockOnCapture);
		PlayerController->SetInputMode(InputMode);
	}
}

void UMyGameInstance::HideMainMenu()
{
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->bShowMouseCursor = false;
		FInputModeGameOnly InputMode;
		PlayerController->SetInputMode(InputMode);
	}
	if (MainMenuWidget)
	{
		MainMenuWidget->SetVisibility(ESlateVisibility::Collapsed);
	}
}

//void UMyGameInstance::MyAsyncLoadLevel(FSoftObjectPath Path)
//{
//	if (!LoadingScreen && LoadingScreenBlueprint)
//	{
//		LoadingScreen = CreateWidget<ULoadingScreen>(this, LoadingScreenBlueprint);
//		LoadingScreen->AddToViewport();
//	}
//	LoadingScreen->SetVisibility(ESlateVisibility::Visible);
//
//	if (MyAssetManager == nullptr)
//	{
//		MyAssetManager = Cast<UMyAssetManager>(GEngine->AssetManager);
//	}
//	if (MyAssetManager)
//	{
//		FString PathString = Path.ToString();
//		/*int32 DotIndex = PathString.Find(TEXT("."));
//		if (DotIndex != INDEX_NONE)
//		{
//			PathString = PathString.Left(DotIndex);
//		}*/
//		PathString = PathString.Replace(TEXT(" "), TEXT(""), ESearchCase::IgnoreCase);
//		TargetPath = PathString;
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, PathString);
//		MyAssetManager->MyAsyncLoadObject(PathString, OnLoadCompleteDelegate);
//		GetWorld()->GetTimerManager().SetTimer(UpdateProgressTimer, this, 
//			&UMyGameInstance::UpdateLoadingScreenProgress,
//			0.1f, true
//		);
//	}
//}
//
//void UMyGameInstance::OnLoadComplete()
//{
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("加载完成"));
//	GetWorld()->GetTimerManager().ClearTimer(UpdateProgressTimer);
//	if (LoadingScreen)
//	{
//		LoadingScreen->SetVisibility(ESlateVisibility::Collapsed);
//	}
//	UGameplayStatics::OpenLevel(GetWorld(), FName(TargetPath.GetAssetName()));
//}
//
//void UMyGameInstance::UpdateLoadingScreenProgress()
//{
//	if (MyAssetManager == nullptr)
//	{
//		MyAssetManager = Cast<UMyAssetManager>(GEngine->AssetManager);
//	}
//	if (MyAssetManager)
//	{
//		float Percent = MyAssetManager->GetCurrentLoadProgress();
//		if (LoadingScreen)
//		{
//			LoadingScreen->UpdateProgressBar(Percent);
//		}
//	}
//}
