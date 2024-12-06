// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShootingConsole.generated.h"

class UStaticMeshComponent;
class UBoxComponent;
class UWidgetComponent;
class ATct_FPSGameMode;
class AMyPlayerController;

UCLASS()
class TCT_FPS_API AShootingConsole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShootingConsole();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	AMyPlayerController* PlayerController;


	TObjectPtr<ATct_FPSGameMode> GameMode;

	UPROPERTY(EditAnywhere, Category = "碰撞 | 柱子")
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(EditAnywhere, Category = "碰撞 | 触发区域")
	TObjectPtr<UBoxComponent> TriggerArea;

	UPROPERTY(EditAnywhere, Category = "模型")
	TObjectPtr<UStaticMeshComponent> ConsoleMesh;

	UPROPERTY(EditAnywhere, Category = "UI")
	TObjectPtr<UWidgetComponent> WidgetComponent;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
	void OnTriggerAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ShowStartBtn();

	void HideStartBtn();
	
	
};
