// CopyRight © Dead Air Game. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DeadAirEditorTarget : TargetRules
{
	public DeadAirEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_6;
		DefaultBuildSettings = BuildSettingsVersion.V5;

		ExtraModuleNames.AddRange(["DeadAir"]);
	}
}
