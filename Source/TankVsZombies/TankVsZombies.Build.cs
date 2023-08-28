// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class TankVsZombies : ModuleRules
{
	public TankVsZombies(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Paper2D" });

		//AI dependencies
		PrivateDependencyModuleNames.AddRange(new string[] { "AIModule", "NavigationSystem", "GameplayTasks"});

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
