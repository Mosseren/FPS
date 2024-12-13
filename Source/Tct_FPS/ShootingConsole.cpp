// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingConsole.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Tct_FPSGameMode.h"

#include "MyPlayerController.h"
#include <Kismet/GameplayStatics.h>
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


// Sets default values
AShootingConsole::AShootingConsole()
{
	//PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Block);
	RootComponent = BoxCollision;

	ConsoleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ConsoleMesh"));
	ConsoleMesh->SetupAttachment(RootComponent);

	TriggerArea = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerArea"));
	TriggerArea->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	TriggerArea->SetCollisionResponseToAllChannels(ECR_Overlap);
	TriggerArea->SetupAttachment(RootComponent);
	TriggerArea->OnComponentBeginOverlap.AddDynamic(this, &AShootingConsole::OnTriggerAreaBeginOverlap);
	TriggerArea->OnComponentEndOverlap.AddDynamic(this, &AShootingConsole::OnTriggerAreaEndOverlap);

	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("3DUIWidget"));
	WidgetComponent->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AShootingConsole::BeginPlay()
{
	Super::BeginPlay();
	GameMode = Cast<ATct_FPSGameMode>(UGameplayStatics::GetGameMode(this));
	HideStartBtn();
}

void AShootingConsole::OnTriggerAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->ActorHasTag(TEXT("Player")))
	{
		return;
	}
	if (GameMode && GameMode->CountDownStatus != ECountDownStatus::Processing)
	{
		ShowStartBtn();
	}
	// 绑定按键
	if (GameMode)
	{
		if (StartBtnMapping)
		{
			GameMode->EnhancedInputSubsystem->AddMappingContext(StartBtnMapping, 1);
		}
		if (!IMC_binded && GameMode && GameMode->EnhancedInputComponent && StartBtnAction)
		{
			GameMode->EnhancedInputComponent->BindAction(StartBtnAction, ETriggerEvent::Triggered, this, &AShootingConsole::StartShooting);
			IMC_binded = true;
		}
	}
}

void AShootingConsole::OnTriggerAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (!OtherActor->ActorHasTag(TEXT("Player")))
	{
		return;
	}
	HideStartBtn();
	 // 取消绑定
	/*if (GameMode && GameMode->EnhancedInputComponent && StartBtnAction)
	{
		GameMode->EnhancedInputComponent->RemoveActionBinding(TEXT("StartBtnAction"), EInputEvent::IE_Pressed);
	}*/
	if (GameMode && GameMode->EnhancedInputSubsystem && StartBtnMapping)
	{
		GameMode->EnhancedInputSubsystem->RemoveMappingContext(StartBtnMapping);
	}
}

void AShootingConsole::StartShooting()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("E pressed"));
	HideStartBtn(); // 隐藏 UI
	GameMode->CoundDown(); // 开始倒计时
}

void AShootingConsole::ShowStartBtn()
{
	if (WidgetComponent)
	{
		WidgetComponent->SetVisibility(true);
	}
}

void AShootingConsole::HideStartBtn()
{
	if (WidgetComponent)
	{
		WidgetComponent->SetVisibility(false);
	}
}

