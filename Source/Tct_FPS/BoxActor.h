// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BoxActor.generated.h"

class UBoxComponent;
class ATct_FPSGameMode;

UCLASS()
class TCT_FPS_API ABoxActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ABoxActor();

protected:
	UPROPERTY(Config)
	int32 iValue;
	bool bIsImportant = false;
	int32 iImportantValueFactor = 2;
	float iScaleFactor;

	bool bHitOnce = false;

	ATct_FPSGameMode* GameMode;
	void MakeBigger();
public:	
	// Box mesh component
	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BoxMesh;

	// Box collision component
	UPROPERTY(EditAnywhere)
	UBoxComponent* BoxCollision;

	void MakeImportant();

	int32 GetValue();

	void OnHitFunc(APlayerController* PlayerController);

	void EnablePhysicsSimulation();
};

