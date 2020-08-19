// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Holdable/ShooterHoldableBase.h"
#include "ShooterWeaponBase.generated.h"

class AShooterCharacterBase;
class USkeletalMeshComponent;
class AShooterPlayerControllerBase;
class UHandleFireComponent;
class UHandleEffectComponent;
class UWeaponPropertiesComponent;

UCLASS()
class SHOOTER_API AShooterWeaponBase : public AShooterHoldableBase
{
	GENERATED_BODY()
public:
	AShooterWeaponBase();

	void Use(const bool bUse) override;

	void SimulateFire(const FVector ShootLocation, const FVector ShootDirection);

	void ApplyFireRecoil(const bool bApplyRecoil, const float VerticalRecoil = 0.f, const float HorizontalRecoil = 0.f);

	void SetOwningPawn(AShooterCharacterBase* NewOwner);
	
	USkeletalMeshComponent* GetMesh();
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	USkeletalMeshComponent* FP_SMeshComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Components)
	USkeletalMeshComponent* TP_SMeshComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Components)
	UWeaponPropertiesComponent* WeaponPropertiesComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Components)
	UHandleFireComponent* HandleFireComponent;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = Components)
	UHandleEffectComponent* HandleEffectComponent;

private:
	AShooterCharacterBase* OwnerCharacter;
	AShooterPlayerControllerBase* OwnerController;
};
