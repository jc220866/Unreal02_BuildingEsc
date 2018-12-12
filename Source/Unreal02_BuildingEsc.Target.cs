// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Unreal02_BuildingEscTarget : TargetRules
{
	public Unreal02_BuildingEscTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Game;

		ExtraModuleNames.AddRange( new string[] { "Unreal02_BuildingEsc" } );
	}
}
