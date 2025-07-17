// CopyRight Dead Air Game. All Rights Reserved.

using UnrealBuildTool;
using System.Collections.Generic;

public class DeadAirEditorTarget : TargetRules
{
	public DeadAirEditorTarget( TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;
		DefaultBuildSettings = BuildSettingsVersion.V5;
		IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_5;
		ExtraModuleNames.AddRange([
			"DeadAir", "DebugTool"
		]);
	}
}
