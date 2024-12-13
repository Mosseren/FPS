// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "MyGameInstance.h"
#include "Kismet/GameplayStatics.h"


void UMainMenu::NativeOnInitialized()
{
	if (LoginBtn)
	{
		LoginBtn->OnClicked.AddDynamic(this, &UMainMenu::OnLoginBtnClicked);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("绑定按键"));
	}
}

void UMainMenu::OnLoginBtnClicked()
{
	UMyGameInstance* MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (MyGameInstance)
	{
		MyGameInstance->HideMainMenu();
	}
	UGameplayStatics::OpenLevel(GetWorld(), NextLevel);
}
