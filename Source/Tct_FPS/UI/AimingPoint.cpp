// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/AimingPoint.h"
#include "Components/Image.h"

void UAimingPoint::ChangeImageColorToRed()
{
	GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, TEXT("尝试变色"));
	if (CenterPoint)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, TEXT("变色"));
		GetWorld()->GetTimerManager().ClearTimer(TimerHandle_ResetColor);
		// 设置Image的颜色为红色
		CenterPoint->SetBrushTintColor(FLinearColor(1.0f, 0.0f, 0.0f, 1.0f));

		// 启动定时器，在0.5秒后调用恢复颜色的函数
		GetWorld()->GetTimerManager().SetTimer(
			TimerHandle_ResetColor,
			this,
			&UAimingPoint::ResetImageColor,
			0.5f,
			false
		);
	}
}

void UAimingPoint::ResetImageColor()
{
	if (CenterPoint)
	{
		// 恢复Image的默认颜色
		CenterPoint->SetBrushTintColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
	}
}



