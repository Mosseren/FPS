// Copyright Epic Games, Inc. All Rights Reserved.

#include "Tct_FPSGameMode.h"
#include "Tct_FPSCharacter.h"
#include "UObject/ConstructorHelpers.h"

ATct_FPSGameMode::ATct_FPSGameMode()
	: Super()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnClassFinder(TEXT("/Game/FirstPerson/Blueprints/BP_FirstPersonCharacter"));
	DefaultPawnClass = PlayerPawnClassFinder.Class;

}
