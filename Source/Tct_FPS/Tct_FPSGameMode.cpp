// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tct_FPSGameMode.h"
#include "Tct_FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "BoxActor.h"
#include <Kismet/GameplayStatics.h>

ATct_FPSGameMode::ATct_FPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;
	PrimaryActorTick.bCanEverTick = true;

	// 读取配置
	GConfig->GetInt(TEXT("/Script/TCT_FPS.ATct_FPSGameMode"), TEXT("iImportantCnt"), iImportantCnt, GGameIni);
	GConfig->GetInt(TEXT("/Script/TCT_FPS.ATct_FPSGameMode"), TEXT("iRoundTime"), iRoundTime, GGameIni);
}

void ATct_FPSGameMode::BeginPlay()
{
	Super::BeginPlay();
	SelectImportantBoxes();
	SetTimer();
}

void ATct_FPSGameMode::Tick(float DeltaTime)
{
}

void ATct_FPSGameMode::SetTimer()
{
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ATct_FPSGameMode::OnTimerComplete, iRoundTime, false);
}

void ATct_FPSGameMode::OnTimerComplete()
{
	bTimeOver = true;
	// 打印分数
	GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Yellow, FString::Printf(TEXT("score = %d"), iScore));
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

	// 随机选择 m 个不同的方块
	while (ChosenIndices.Num() < iImportantCnt)
	{
		// 随机生成一个下标
		int32 RandomIndex = FMath::RandRange(0, AllBoxes.Num() - 1);

		while (ChosenIndices.Contains(RandomIndex))
		{
			RandomIndex = (RandomIndex + 1) % AllBoxes.Num();  // 循环递增，直到不重复
		}

		ChosenIndices.Add(RandomIndex);

		// 选中方块设为重要
		ABoxActor* SelectedBlock = Cast<ABoxActor>(AllBoxes[RandomIndex]);
		if (SelectedBlock)
		{
			SelectedBlock->MakeImportant();
		}
	}
}

void ATct_FPSGameMode::AddScore(int32 Value)
{
	if (!bTimeOver) {
		GEngine->AddOnScreenDebugMessage(-1, 10.f, FColor::Red, FString::Printf(TEXT("add score = %d"), Value));
		iScore += Value;
	}
}
