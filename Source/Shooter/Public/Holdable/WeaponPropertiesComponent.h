// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Common/CommonTypes.h"
#include "Components/ActorComponent.h"
#include "WeaponPropertiesComponent.generated.h"

class AShooterCharacterBase;
class AShooterGunProjectileBase;

UCLASS( ClassGroup=(Weapon), meta=(BlueprintSpawnableComponent) )
class SHOOTER_API UWeaponPropertiesComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UWeaponPropertiesComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	uint32 GetCurrentAmmoInClip() const;

	void UseAmmo(uint32 UseNum = 1);

	void HandleUseAmmo(uint32 UseNum);

	EGunState GetCurrentGunState() const;

	void SetGunState(const EGunState NewState);

	void HandleSetGunState(const EGunState NewState);

	UFUNCTION()
	void OnRep_AmmoNumber();

	UFUNCTION()
	void OnRep_MaxAmmoNumber();

	UFUNCTION()
	void OnRep_GunState();
public:
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_UseAmmo(const uint32 UseName);
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_SetGunState(const EGunState NewState);
public:
	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	bool	bInfiniteAmmo;

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	uint32	MaxAmmoInClip;

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	uint32	MaxAmmo;

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	uint32	BurstCount;

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
	TSubclassOf<AShooterGunProjectileBase> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category = GunState)
	float	ShootRange;

	UPROPERTY(EditDefaultsOnly, Category = GunState)
	float	ShootBetweenTime;

	UPROPERTY(EditDefaultsOnly, Category = GunState)
	float	ShootCoolDownTime;

	UPROPERTY(EditDefaultsOnly, Category = GunState)
	EGunFireMode FireMode;

	UPROPERTY(EditDefaultsOnly, Category = Recoil)
	float	VerticalRecoilBase;
	UPROPERTY(EditDefaultsOnly, Category = Recoil)
	float	VerticalRecoilAcceleration;
	UPROPERTY(EditDefaultsOnly, Category = Recoil)
	float	HorizontalRecoilBase;
	UPROPERTY(EditDefaultsOnly, Category = Recoil)
	float	HorizontalRecoilAcceleration;

	UPROPERTY(EditDefaultsOnly, Category = Recoil)
	bool	AutoRecoverRecoil;

	UPROPERTY(EditDefaultsOnly, Category = Recoil)
	float	VerRecoilRecoverSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Recoil)
	float	VerticalRecoilTime;

	UPROPERTY(EditDefaultsOnly, Category = Recoil)
	float	MaximumPitchAngle;

private:
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_AmmoNumber)
	uint32	_Ammo;

	UPROPERTY(Replicated, ReplicatedUsing = OnRep_MaxAmmoNumber)
	uint32	_MaxAmmo;

	UPROPERTY(Replicated, ReplicatedUsing = OnRep_GunState)
	EGunState _GunState;

private:
	AShooterCharacterBase* OwnerCharacter;
};
