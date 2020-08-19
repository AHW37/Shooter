// Fill out your copyright notice in the Description page of Project Settings.


#include "Controller/ShooterPlayerControllerBase.h"

void AShooterPlayerControllerBase::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
}

void AShooterPlayerControllerBase::OnUnPossess()
{
	Super::OnUnPossess();
}

void AShooterPlayerControllerBase::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (InputComponent)
	{
		InputComponent->BindAxis("MoveForward", this, &AShooterPlayerControllerBase::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &AShooterPlayerControllerBase::MoveRight);
		InputComponent->BindAxis("Turn", this, &AShooterPlayerControllerBase::Turn);
		InputComponent->BindAxis("TurnRate", this, &AShooterPlayerControllerBase::TurnRate);
		InputComponent->BindAxis("LookUp", this, &AShooterPlayerControllerBase::LookUp);
		InputComponent->BindAxis("LookUpRate", this, &AShooterPlayerControllerBase::LookUpRate);

		InputComponent->BindAction("SwitchWeapon", EInputEvent::IE_Pressed, this, &AShooterPlayerControllerBase::SwitchWeapon);

		InputComponent->BindAction("Fire", EInputEvent::IE_Pressed, this, &AShooterPlayerControllerBase::FirePressed);
		InputComponent->BindAction("Fire", EInputEvent::IE_Released, this, &AShooterPlayerControllerBase::FireReleased);

		InputComponent->BindAction("Aim", EInputEvent::IE_Pressed, this, &AShooterPlayerControllerBase::AimPressed);
		InputComponent->BindAction("Aim", EInputEvent::IE_Released, this, &AShooterPlayerControllerBase::AimReleased);

		InputComponent->BindTouch(EInputEvent::IE_Pressed, this, &AShooterPlayerControllerBase::OnTouchPressed);
		InputComponent->BindTouch(EInputEvent::IE_Released, this, &AShooterPlayerControllerBase::OnTouchReleased);
		InputComponent->BindTouch(EInputEvent::IE_Repeat, this, &AShooterPlayerControllerBase::OnTouchRepeat);
	}
}

void AShooterPlayerControllerBase::MoveForward(float AxisValue)
{
	APawn* aPawn = GetPawn();
	if (aPawn)
	{
		aPawn->AddMovementInput(GetControlRotation().Vector(), AxisValue);
	}
}

void AShooterPlayerControllerBase::MoveRight(float AxisValue)
{
	APawn* aPawn = GetPawn();
	if (aPawn)
	{
		aPawn->AddMovementInput(FRotationMatrix(GetControlRotation()).GetScaledAxis(EAxis::Y), AxisValue);
	}
}

void AShooterPlayerControllerBase::Turn(float AxisValue)
{
	AddYawInput(AxisValue);
}

void AShooterPlayerControllerBase::TurnRate(float AxisValue)
{
}

void AShooterPlayerControllerBase::LookUp(float AxisValue)
{
	AddPitchInput(AxisValue);
}

void AShooterPlayerControllerBase::LookUpRate(float AxisValue)
{
}

void AShooterPlayerControllerBase::OnTouchPressed(ETouchIndex::Type FingerIndex, FVector Location)
{

}

void AShooterPlayerControllerBase::OnTouchReleased(ETouchIndex::Type FingerIndex, FVector Location)
{

}

void AShooterPlayerControllerBase::OnTouchRepeat(ETouchIndex::Type FingerIndex, FVector Location)
{

}

void AShooterPlayerControllerBase::SwitchWeapon()
{

}

void AShooterPlayerControllerBase::FirePressed()
{

}

void AShooterPlayerControllerBase::FireReleased()
{

}

void AShooterPlayerControllerBase::AimPressed()
{

}

void AShooterPlayerControllerBase::AimReleased()
{

}
