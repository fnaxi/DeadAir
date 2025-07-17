// CopyRight Dead Air Game. All Rights Reserved.

using UnrealBuildTool;

public class DebugTool : ModuleRules
{
	public DebugTool(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange([
			"Core"
		]);

		PrivateDependencyModuleNames.AddRange([
			"CoreUObject",
			"Engine",
			"Slate",
			"SlateCore",
			"UMG",
			"ImGui", 
			"DeadAir"
		]);
	}
}
