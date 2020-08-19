// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CommonTypes.generated.h"


UENUM(BlueprintType)
enum class EGunFireMode : uint8
{
	Mode_None,
	Mode_Single,
	Mode_Burst,
	Mode_Auto,
	Mode_Chamber,
};

UENUM(BlueprintType)
enum class EGunState : uint8
{
	State_None,
	State_Idle,
	State_Firing,
	State_FireDelay,
	State_Reloading,
	State_Chamber,
	State_Max,
};