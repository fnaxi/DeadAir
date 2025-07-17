// CopyRight Dead Air Game. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DeadAirTarget : TargetRules
{
	public DeadAirTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.AddRange(new[]
		{
			"DeadAir", "DebugTool"
		});
	}
}
