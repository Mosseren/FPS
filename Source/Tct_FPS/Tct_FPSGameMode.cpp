// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tct_FPSGameMode.h"
#include "Tct_FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BoxActor.h"
#include <Kismet/GameplayStatics.h>
#include "MyPlayerController.h"

ATct_FPSGameMode::ATct_FPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_MyPlayerController"));
	PlayerControllerClass = PlayerControllerClassFinder.Class;

	PrimaryActorTick.bCanEverTick = true;

	// ��ȡ����
	GConfig->GetInt(TEXT("/Script/TCT_FPS.ATct_FPSGameMode"), TEXT("iImportantCnt"), iImportantCnt, GGameIni);
	GConfig->GetInt(TEXT("/Script/TCT_FPS.ATct_FPSGameMode"), TEXT("iRoundTime"), iRoundTime, GGameIni);

}

void ATct_FPSGameMode::BeginPlay()
{
	Super::BeginPlay();

	if (PlayerController == nullptr)
	{
		PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	}
	SelectImportantBoxes();
	PlayerController->InitializeHUD();

	CountDownStatus = ECountDownStatus::Unstarted;
}

void ATct_FPSGameMode::Tick(float DeltaTime)
{
}

void ATct_FPSGameMode::CoundDown()
{
	TimeRemaining = iRoundTime;
	CountDownStatus = ECountDownStatus::Processing;
	GetWorld()->GetTimerManager().SetTimer(UpdateHandle, this, &ATct_FPSGameMode::UpdateHUDTime, 1.f, true, 1.f);
}

void ATct_FPSGameMode::UpdateHUDTime()
{
	if (TimeRemaining > 0)
	{
		TimeRemaining -= 1;
		PlayerController->SetTime(FString::FromInt(TimeRemaining));
	}
	else
	{
		CountDownStatus = ECountDownStatus::TimeOver;
		GetWorld()->GetTimerManager().ClearTimer(UpdateHandle);
	}
}

void ATct_FPSGameMode::SelectImportantBoxes()
{
	TArray<AActor*> AllBoxes;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), ABoxActor::StaticClass(), AllBoxes);

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, FString::Printf(TEXT("box num = %d"), AllBoxes.Num()));

	if (AllBoxes.Num() < iImportantCnt)
	{
		UE_LOG(LogTemp, Warning, TEXT("Not enough blocks available!"));
		return;
	}

	TSet<int32> ChosenIndices;

	// ���ѡ�� m ����ͬ�ķ���
	while (ChosenIndices.Num() < iImportantCnt)
	{
		// �������һ���±�
		int32 RandomIndex = FMath::RandRange(0, AllBoxes.Num() - 1);

		while (ChosenIndices.Contains(RandomIndex))
		{
			RandomIndex = (RandomIndex + 1) % AllBoxes.Num();  // ѭ��������ֱ�����ظ�
		}

		ChosenIndices.Add(RandomIndex);

		// ѡ�з�����Ϊ��Ҫ
		ABoxActor* SelectedBlock = Cast<ABoxActor>(AllBoxes[RandomIndex]);
		if (SelectedBlock)
		{
			SelectedBlock->MakeImportant();
		}
	}
} 

void ATct_FPSGameMode::AddScore(int32 Value)
{
	if (CountDownStatus == ECountDownStatus::Processing) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("add score = %d"), Value));
		iScore += Value;
		
		if (PlayerController == nullptr)
		{
			UE_LOG(LogTemp, Error, TEXT("PlayerController is nullptr"));
		}
		else
		{
			PlayerController->SetScore(FString::FromInt(iScore));
		}
	}
}
