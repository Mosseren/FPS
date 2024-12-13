// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "MyAssetManager.generated.h"


DECLARE_DYNAMIC_DELEGATE(FOnPackageLoaded);

UCLASS(Blueprintable)
class TCT_FPS_API UMyAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	FString CurrentLoadPackage;

	// 静态获取实例函数
	UFUNCTION(BlueprintPure, CallInEditor, DisplayName = "MyAssetManager")
	static UMyAssetManager* Get();

	// 异步加载对象
	UFUNCTION(BlueprintCallable, CallInEditor)
	FString MyAsyncLoadObject(FSoftObjectPath Path, FOnPackageLoaded OnPackageLoaded);

	// 获取当前加载进度
	UFUNCTION(BlueprintCallable, CallInEditor)
	float GetCurrentLoadProgress() const;
};