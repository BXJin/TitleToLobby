// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class Title2Lobby : ModuleRules
{
	public Title2Lobby(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", 
            "UMG", "OnlineSubsystem", "OnlineSubsystemUtils", "AdvancedSessions" });


        PrivateDependencyModuleNames.AddRange(new string[] {  });

        DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");

        PublicIncludePaths.AddRange(new string[] { "Title2Lobby" });
        // Uncomment if you are using Slate UI
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        //PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
