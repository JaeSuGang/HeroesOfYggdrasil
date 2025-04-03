// Copyright Epic Games, Inc. All Rights Reserved.

using System.IO;
using UnrealBuildTool;

public class HeroesOfYggdrasilEditor : ModuleRules
{
	public HeroesOfYggdrasilEditor(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "HeroesOfYggdrasil", "Slate", "SlateCore" });
    }
}
