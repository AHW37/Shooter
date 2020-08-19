// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HandleFireComponent.generated.h"

class AShooterWeaponBase;
class AShooterCharacterBase;
class AShooterPlayerControllerBase;
class UHandleEffectComponent;
class UWeaponPropertiesComponent;

UCLASS( ClassGroup=(Weapon), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UHandleFireComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UHandleFireComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	void StartFire();

	void StopFire(const bool bInterruptFire = true);

	UFUNCTION()
	void HandleFire();

	void HandleFireEnd();

	void EnterFireCoolDown();
	UFUNCTION()
	void ExitFireCoolDown();

	void CalculateRecoil(const uint32 CurrentFireCount);

	float CalculateSpread(const uint32 CurrentFireCount);

	bool CalculateAimDirection(FVector& ShootLocation, FVector& ShootDirection);

	bool WeaponStateCheck() const;

	bool OwnerPawnStateCheck() const;

	bool CheckAutoReload() const;

	bool HasAmmoInClip() const;
public:
private:
	uint32 FireCount;
	FTimerHandle Timer_FireBetween;

	FVector ShootSpawnLocation;
	FVector ShootSpawnDirection;

	AShooterWeaponBase* OwnerWeapon;
	AShooterCharacterBase* OwnerCharacter;
	AShooterPlayerControllerBase* OwnerController;
	UWeaponPropertiesComponent* WeaponPropertiesComponent;
	UHandleEffectComponent* HandleEffectComponent;
};
