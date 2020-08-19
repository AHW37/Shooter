// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "ShooterPlayerControllerBase.generated.h"

/**
 * 
 */
UCLASS()
class SHOOTER_API AShooterPlayerControllerBase : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void OnPossess(APawn* aPawn) override;
	virtual void OnUnPossess() override;

public:
	virtual void SetupInputComponent() override;

public:
	UFUNCTION()
	void MoveForward(float AxisValue);
	UFUNCTION()
	void MoveRight(float AxisValue);
	UFUNCTION()
	void Turn(float AxisValue);
	UFUNCTION()
	void TurnRate(float AxisValue);
	UFUNCTION()
	void LookUp(float AxisValue);
	UFUNCTION()
	void LookUpRate(float AxisValue);

	UFUNCTION()
	void OnTouchPressed(ETouchIndex::Type FingerIndex, FVector Location);
	UFUNCTION()
	void OnTouchReleased(ETouchIndex::Type FingerIndex, FVector Location);
	UFUNCTION()
	void OnTouchRepeat(ETouchIndex::Type FingerIndex, FVector Location);

	UFUNCTION()
	void SwitchWeapon();

	UFUNCTION()
	void FirePressed();
	UFUNCTION()
	void FireReleased();

	UFUNCTION()
	void AimPressed();
	UFUNCTION()
	void AimReleased();
};
