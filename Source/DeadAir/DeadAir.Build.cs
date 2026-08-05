// CopyRight © Dead Air Game. All Rights Reserved.

using UnrealBuildTool;

public class DeadAir : ModuleRules
{
	public DeadAir(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(
		[
			"Core",
			"CoreUObject",
			
			"Engine",
			
			"InputCore",
			"EnhancedInput",
			
			"HeadMountedDisplay",
			"UMG"
		]);

		PrivateDependencyModuleNames.AddRange(
		[
			// ...
		]);

		// Uncomment if you are using Slate UI
		PrivateDependencyModuleNames.AddRange(["Slate", "SlateCore"]);
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
