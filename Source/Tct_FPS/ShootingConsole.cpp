// Fill out your copyright notice in the Description page of Project Settings.


#include "ShootingConsole.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Tct_FPSGameMode.h"

#include "MyPlayerController.h"
#include <Kismet/GameplayStatics.h>


// Sets default values
AShootingConsole::AShootingConsole()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

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
	if (PlayerController == nullptr)
	{
		PlayerController = Cast<AMyPlayerController>(GetWorld()->GetFirstPlayerController());
	}
	GameMode = Cast<ATct_FPSGameMode>(UGameplayStatics::GetGameMode(this));
	HideStartBtn();
}

// Called every frame
void AShootingConsole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (PlayerController->IsInputKeyDown(EKeys::E) && GameMode && GameMode->CountDownStatus != ECountDownStatus::Processing)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Red, TEXT("E pressed"));
		HideStartBtn(); // 隐藏 UI
		GameMode->CoundDown(); // 开始倒计时
	}
}

void AShootingConsole::OnTriggerAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GameMode && GameMode->CountDownStatus != ECountDownStatus::Processing)
	{
		ShowStartBtn();
	}
}

void AShootingConsole::OnTriggerAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	HideStartBtn();
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

