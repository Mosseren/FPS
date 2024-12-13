// Fill out your copyright notice in the Description page of Project Settings.


#include "MyAssetManager.h"

UMyAssetManager* UMyAssetManager::Get()
{
	UMyAssetManager* This = Cast<UMyAssetManager>(GEngine->AssetManager);
	if (This)
	{
		return This;
	}
	else
	{
		return NewObject<UMyAssetManager>();
	}
}

FString UMyAssetManager::MyAsyncLoadObject(FSoftObjectPath Path, FOnPackageLoaded OnPackageLoaded) {
	FString result;
	// 输出加载路径
	result.Append(FString::Printf(TEXT("StartLoad: \t%s\n"), *Path.ToString()));
	CurrentLoadPackage = Path.ToString();

	// 异步加载包
	LoadPackageAsync(CurrentLoadPackage,
		FLoadPackageAsyncDelegate::CreateLambda([=](const FName& PackageName, UPackage* LoadedPackage, EAsyncLoadingResult::Type Result) {
			if (Result == EAsyncLoadingResult::Succeeded) {
				// 执行通知以进行地图切换
				OnPackageLoaded.ExecuteIfBound();
			}
			}), 0, PKG_ContainsMap);

	return result;
}

float UMyAssetManager::GetCurrentLoadProgress() const {
	return GetAsyncLoadPercentage(*CurrentLoadPackage);
}
