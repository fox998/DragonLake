// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DragonLern : ModuleRules
{
	public DragonLern(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "HeadMountedDisplay", "Slate" });
	}
}
