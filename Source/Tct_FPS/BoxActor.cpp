// Fill out your copyright notice in the Description page of Project Settings.


#include "BoxActor.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Engine/Engine.h"
#include "Tct_FPSGameMode.h"
#include <Kismet/GameplayStatics.h>
#include "MyPlayerController.h"


// Sets default values
ABoxActor::ABoxActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create collision component
	BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxCollision"));
	BoxCollision->SetBoxExtent(FVector(50.0f, 50.0f, 50.0f));
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Block);
	RootComponent = BoxCollision;

	// Create mesh component and set it as root
	BoxMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BoxMesh"));
	BoxMesh->SetupAttachment(RootComponent);
	//EnablePhysicsSimulation();
	BoxCollision->SetSimulatePhysics(false);

	Tags.Add(FName("Box"));

	// 读取配置
	GConfig->GetInt(TEXT("/Script/TCT_FPS.ABoxActor"), TEXT("iValue"), iValue, GGameIni);
	GConfig->GetFloat(TEXT("/Script/TCT_FPS.ABoxActor"), TEXT("iScaleFactor"), iScaleFactor, GGameIni);
}


void ABoxActor::MakeBigger()
{
	FVector NewScale = BoxCollision->GetComponentScale() * iScaleFactor;
	BoxCollision->SetWorldScale3D(NewScale);
}

void ABoxActor::MakeImportant()
{
	bIsImportant = true;
	// 获取mesh 创建材质 改色
	UStaticMeshComponent* MeshComponent = FindComponentByClass<UStaticMeshComponent>();
	if (MeshComponent)
	{
		UMaterialInstanceDynamic* DynMaterial = MeshComponent->CreateDynamicMaterialInstance(0);
		if (DynMaterial)
		{
			UE_LOG(LogTemp, Warning, TEXT("!!!mat created!"));
			DynMaterial->SetVectorParameterValue("Base Color", FLinearColor::Red);
		}
	}
}

int32 ABoxActor::GetValue()
{
	return bIsImportant ? iValue * iImportantValueFactor : iValue;
}


void ABoxActor::OnHitFunc(APlayerController* CasterPlayer)
{
	if (GameMode == nullptr) {
		GameMode = Cast<ATct_FPSGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	}
	if (GameMode == nullptr) {
		UE_LOG(LogTemp, Error, TEXT("current gamemode is not ATct_FPSGameMode!!!"));
		return;
	}
	if(GameMode->CountDownStatus != ECountDownStatus::Processing)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, FString::Printf(TEXT("hitOnce?=%s"), bHitOnce ? TEXT("true") : TEXT("false")));
	if (!bHitOnce)
	{
		bHitOnce = true;
		MakeBigger();
	}
	else
	{
		Destroy();
	}

	// 得分
	GameMode->AddScore(GetValue());
	// 命中准星处理
	AMyPlayerController* MyPlayerController = Cast<AMyPlayerController>(CasterPlayer);
	if (MyPlayerController)
	{
		MyPlayerController->OnHitAnimAimingPoint();
	}
}

// Enable physics simulation on the box
void ABoxActor::EnablePhysicsSimulation()
{
	// 启用物理模拟
	BoxCollision->SetSimulatePhysics(true);
	// 设置物理模拟的质量、重力
	BoxCollision->SetMassOverrideInKg(NAME_None, 50.f, true);
	BoxCollision->SetEnableGravity(true);
	// 设置摩擦力和弹性
	BoxCollision->SetLinearDamping(0.5f);
	BoxCollision->SetAngularDamping(0.5f);
}

