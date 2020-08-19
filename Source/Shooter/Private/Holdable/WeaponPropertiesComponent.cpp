// Fill out your copyright notice in the Description page of Project Settings.


#include "Holdable/WeaponPropertiesComponent.h"
#include "Character/ShooterCharacterBase.h"
#include "Net/UnrealNetwork.h"

// Sets default values for this component's properties
UWeaponPropertiesComponent::UWeaponPropertiesComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void UWeaponPropertiesComponent::BeginPlay()
{
	Super::BeginPlay();

	OwnerCharacter = Cast<AShooterCharacterBase>(GetOwner());
}


// Called every frame
void UWeaponPropertiesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

uint32 UWeaponPropertiesComponent::GetCurrentAmmoInClip() const
{
	return _Ammo;
}

void UWeaponPropertiesComponent::UseAmmo(uint32 UseNum/* = 1*/)
{
	if (OwnerCharacter && OwnerCharacter->GetLocalRole() == ROLE_Authority)
	{
		HandleUseAmmo(UseNum);
	}
	else
	{
		Server_UseAmmo(UseNum);
	}
}

void UWeaponPropertiesComponent::HandleUseAmmo(uint32 UseNum)
{
	if (_Ammo - UseNum >= 0)
	{
		_Ammo -= UseNum;
	}
}

EGunState UWeaponPropertiesComponent::GetCurrentGunState() const
{
	return _GunState;
}

void UWeaponPropertiesComponent::SetGunState(const EGunState NewState)
{
	if (OwnerCharacter && OwnerCharacter->GetLocalRole() == ROLE_Authority)
	{
		HandleSetGunState(NewState);
	}
	else
	{
		Server_SetGunState(NewState);
	}
}

void UWeaponPropertiesComponent::HandleSetGunState(const EGunState NewState)
{
	if (NewState != _GunState)
	{
		_GunState = NewState;
	}
}

void UWeaponPropertiesComponent::OnRep_AmmoNumber()
{

}

void UWeaponPropertiesComponent::OnRep_MaxAmmoNumber()
{

}

void UWeaponPropertiesComponent::OnRep_GunState()
{

}

void UWeaponPropertiesComponent::Server_SetGunState_Implementation(const EGunState NewState)
{
	SetGunState(NewState);
}

bool UWeaponPropertiesComponent::Server_SetGunState_Validate(const EGunState NewState)
{
	return true;
}

void UWeaponPropertiesComponent::Server_UseAmmo_Implementation(const uint32 UseName)
{
	UseAmmo(UseName);
}

bool UWeaponPropertiesComponent::Server_UseAmmo_Validate(const uint32 UseName)
{
	return true;
}

void UWeaponPropertiesComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	DOREPLIFETIME_CONDITION(UWeaponPropertiesComponent, _Ammo, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UWeaponPropertiesComponent, _MaxAmmo, COND_OwnerOnly);
	DOREPLIFETIME_CONDITION(UWeaponPropertiesComponent, _GunState, COND_OwnerOnly);
}