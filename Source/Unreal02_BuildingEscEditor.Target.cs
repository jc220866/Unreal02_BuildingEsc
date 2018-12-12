// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;
using System.Collections.Generic;

public class Unreal02_BuildingEscEditorTarget : TargetRules
{
	public Unreal02_BuildingEscEditorTarget(TargetInfo Target) : base(Target)
	{
		Type = TargetType.Editor;

		ExtraModuleNames.AddRange( new string[] { "Unreal02_BuildingEsc" } );
	}
}
