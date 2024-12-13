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
class UInputAction;
class UInputMappingContext;

UCLASS()
class TCT_FPS_API AShootingConsole : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShootingConsole();

protected:
	bool IMC_binded = false;

	virtual void BeginPlay() override;

	TObjectPtr<ATct_FPSGameMode> GameMode;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UBoxComponent> TriggerArea;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> ConsoleMesh;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UWidgetComponent> WidgetComponent;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputAction* StartBtnAction;
	UPROPERTY(EditDefaultsOnly, Category = "Input")
	UInputMappingContext* StartBtnMapping;

	void StartShooting();

public:	

	UFUNCTION()
	void OnTriggerAreaBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnTriggerAreaEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
		UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ShowStartBtn();

	void HideStartBtn();
	
};
