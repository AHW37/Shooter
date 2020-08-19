// Fill out your copyright notice in the Description page of Project Settings.


#include "Holdable/ShooterWeaponBase.h"
#include "Holdable/WeaponPropertiesComponent.h"
#include "Holdable/HandleFireComponent.h"
#include "Holdable/HandleEffectComponent.h"
#include "Character/ShooterCharacterBase.h"
#include "Controller/ShooterPlayerControllerBase.h"
#include "Components/SkeletalMeshComponent.h"

AShooterWeaponBase::AShooterWeaponBase()
{
	FP_SMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_SMeshComponent"));
	RootComponent = FP_SMeshComponent;
	FP_SMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	FP_SMeshComponent->SetOnlyOwnerSee(true);
	FP_SMeshComponent->SetOwnerNoSee(false);

	TP_SMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("TP_SMeshComponent"));
	TP_SMeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	TP_SMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	TP_SMeshComponent->SetOwnerNoSee(true);
	TP_SMeshComponent->SetOnlyOwnerSee(false);

	WeaponPropertiesComponent = CreateDefaultSubobject<UWeaponPropertiesComponent>(TEXT("WeaponPropertiesComponent"));
	WeaponPropertiesComponent->SetIsReplicated(true);

	HandleFireComponent = CreateDefaultSubobject<UHandleFireComponent>(TEXT("HandleFireComponent"));
	//HandleFireComponent->SetIsReplicated(true);

	HandleEffectComponent = CreateDefaultSubobject<UHandleEffectComponent>(TEXT("HandleEffectComponent"));
	HandleEffectComponent->SetIsReplicated(true);
}

void AShooterWeaponBase::Use(const bool bUse)
{
	Super::Use(bUse);

	if (NULL == HandleFireComponent)
	{
		return;
	}

	if (bUse)
	{
		HandleFireComponent->StartFire();
	}
	else
	{
		HandleFireComponent->StopFire();
	}
}

void AShooterWeaponBase::SimulateFire(const FVector ShootLocation, const FVector ShootDirection)
{
	if (HandleEffectComponent)
	{
		//HandleEffectComponent
	}
}

void AShooterWeaponBase::ApplyFireRecoil(const bool bApplyRecoil, const float VerticalRecoil /*= 0.f*/, const float HorizontalRecoil /*= 0.f*/)
{

}

void AShooterWeaponBase::SetOwningPawn(AShooterCharacterBase* NewOwner)
{
	SetInstigator(NewOwner);
	OwnerCharacter = NewOwner;
	SetOwner(NewOwner);
}

USkeletalMeshComponent* AShooterWeaponBase::GetMesh()
{
	return (OwnerCharacter != NULL && OwnerCharacter->IsFirstPerson()) ? FP_SMeshComponent : TP_SMeshComponent;
}
