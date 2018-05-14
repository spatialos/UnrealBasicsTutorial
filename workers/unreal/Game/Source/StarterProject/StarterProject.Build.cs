// Copyright (c) Improbable Worlds Ltd, All Rights Reserved

using System;
using System.Collections.Generic;
using UnrealBuildTool;
using System.IO;

public class StarterProject : ModuleRules
{
	public StarterProject(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = ModuleRules.PCHUsageMode.UseExplicitOrSharedPCHs;
		bFasterWithoutUnity = true;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "SpatialOS"});
	}
}
