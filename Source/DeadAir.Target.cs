// CopyRight © Dead Air Game. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DeadAirTarget : TargetRules
{
	public DeadAirTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange(["DeadAir"]);
	}
}
