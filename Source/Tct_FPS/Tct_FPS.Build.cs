// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Tct_FPS : ModuleRules
{
	public Tct_FPS(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
