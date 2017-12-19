// Copyright (c) Improbable Worlds Ltd, All Rights Reserved

using System;
using System.Collections.Generic;
using UnrealBuildTool;
using System.IO;

public class StarterProject : ModuleRules
{
#if !WITH_FORWARDED_MODULE_RULES_CTOR
	// Backwards compatibility with Unreal 4.15
	public StarterProject(TargetInfo Target)
#else
	// Unreal 4.16+
	public StarterProject(ReadOnlyTargetRules Target) : base(Target)
#endif
	{
        PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
				bFasterWithoutUnity = true;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "SpatialOS"});
	}
}
