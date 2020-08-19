// Fill out your copyright notice in the Description page of Project Settings.


#include "Holdable/HandleFireComponent.h"
#include "Holdable/ShooterWeaponBase.h"
#include "Holdable/WeaponPropertiesComponent.h"
#include "Holdable/HandleEffectComponent.h"
#include "Common/CommonTypes.h"
#include "Character/ShooterCharacterBase.h"
#include "Controller/ShooterPlayerControllerBase.h"

// Sets default values for this component's properties
UHandleFireComponent::UHandleFireComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	ShootSpawnLocation = FVector::ZeroVector;
	ShootSpawnDirection = FVector::ZeroVector;
}


// Called when the game starts
void UHandleFireComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerWeapon = Cast<AShooterWeaponBase>(GetOwner());
	if (OwnerWeapon)
	{
		WeaponPropertiesComponent = Cast<UWeaponPropertiesComponent>(OwnerWeapon->GetComponentByClass(UWeaponPropertiesComponent::StaticClass()));
		HandleEffectComponent = Cast<UHandleEffectComponent>(OwnerWeapon->GetComponentByClass(UHandleEffectComponent::StaticClass()));

		OwnerCharacter = Cast<AShooterCharacterBase>(OwnerWeapon->GetOwner());
		if (OwnerCharacter)
		{
			OwnerController = Cast<AShooterPlayerControllerBase>(OwnerCharacter->GetController());
		}
	}
}


// Called every frame
void UHandleFireComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UHandleFireComponent::StartFire()
{
	if (WeaponStateCheck() && OwnerPawnStateCheck())
	{
		HandleFire();

		if (WeaponPropertiesComponent->FireMode == EGunFireMode::Mode_Auto || WeaponPropertiesComponent->FireMode == EGunFireMode::Mode_Burst)
		{
			GetWorld()->GetTimerManager().SetTimer(Timer_FireBetween, this, &UHandleFireComponent::HandleFire, WeaponPropertiesComponent->ShootBetweenTime, true);
		}
	}
	else
	{
		CheckAutoReload();
	}
}

void UHandleFireComponent::StopFire(const bool bInterruptFire /*= true*/)
{
	if (WeaponPropertiesComponent && WeaponPropertiesComponent->GetCurrentGunState() == EGunState::State_Idle)
	{
		return;
	}

	if (bInterruptFire)
	{
		if (WeaponPropertiesComponent->FireMode == EGunFireMode::Mode_Burst)
		{
			return;
		}
	}

	if (OwnerWeapon)
	{
		OwnerWeapon->ApplyFireRecoil(false);
	}

	EnterFireCoolDown();	

	CheckAutoReload();
}

void UHandleFireComponent::HandleFire()
{
	if (WeaponStateCheck() && HasAmmoInClip())
	{
		FireCount++;

		if (WeaponPropertiesComponent)
		{
			WeaponPropertiesComponent->SetGunState(EGunState::State_Firing);
			WeaponPropertiesComponent->UseAmmo();
		}

		CalculateSpread(FireCount);
		CalculateRecoil(FireCount);
		CalculateAimDirection(ShootSpawnLocation, ShootSpawnDirection);

		if (OwnerWeapon)
		{
			OwnerWeapon->SimulateFire(ShootSpawnLocation, ShootSpawnDirection);
		}

		HandleFireEnd();
	}
	else
	{
		StopFire(false);
	}
}

void UHandleFireComponent::HandleFireEnd()
{
	switch (WeaponPropertiesComponent->FireMode)
	{
	case EGunFireMode::Mode_Single:StopFire(false);; break;
	case EGunFireMode::Mode_Burst:
	{
		if (FireCount >= WeaponPropertiesComponent->BurstCount)
		{
			StopFire(false);
		}
		break;
	}
	case EGunFireMode::Mode_Auto:break;
	case EGunFireMode::Mode_Chamber:StopFire(false);; break;
	default:break;
	}
}

void UHandleFireComponent::EnterFireCoolDown()
{
	if (!GetWorld()->GetTimerManager().IsTimerActive(Timer_FireBetween))
	{
		WeaponPropertiesComponent->SetGunState(EGunState::State_FireDelay);
		GetWorld()->GetTimerManager().SetTimer(Timer_FireBetween, this, &UHandleFireComponent::ExitFireCoolDown, WeaponPropertiesComponent->ShootBetweenTime, false);
	}
}

void UHandleFireComponent::ExitFireCoolDown()
{
	FireCount = 0;
	WeaponPropertiesComponent->SetGunState(EGunState::State_Idle);
	GetWorld()->GetTimerManager().ClearTimer(Timer_FireBetween);
}

void UHandleFireComponent::CalculateRecoil(const uint32 CurrentFireCount)
{

}

float UHandleFireComponent::CalculateSpread(const uint32 CurrentFireCount)
{
	return 0.f;
}

bool UHandleFireComponent::CalculateAimDirection(FVector& ShootLocation, FVector& ShootDirection)
{
	return false;
}

bool UHandleFireComponent::WeaponStateCheck() const
{
	if (WeaponPropertiesComponent && WeaponPropertiesComponent->GetCurrentGunState() == EGunState::State_Idle && HasAmmoInClip())
	{
		return true;
	}
	return false;
}

bool UHandleFireComponent::OwnerPawnStateCheck() const
{
	return true;
}

bool UHandleFireComponent::CheckAutoReload() const
{
	return false;
}

bool UHandleFireComponent::HasAmmoInClip() const
{
	if (WeaponPropertiesComponent && WeaponPropertiesComponent->GetCurrentAmmoInClip() > 0)
	{
		return true;
	}
	return false;
}

