// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "ShooterHUDBase.generated.h"

class UUserWidget;

UCLASS()
class SHOOTER_API AShooterHUDBase : public AHUD
{
	GENERATED_BODY()
	
public:
	void ShowHUD() override;

// public:
// 	UPROPERTY(EditDefaultsOnly, Category = HUD)
// 	TSubclassOf<UUserWidget> HUDClass;
// 
// private:
// 	UUserWidget* HUD;
};
