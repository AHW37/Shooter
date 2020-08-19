// Fill out your copyright notice in the Description page of Project Settings.


#include "Holdable/ShooterHoldableBase.h"
#include "Net/UnrealNetwork.h"

// Sets default values
AShooterHoldableBase::AShooterHoldableBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SetReplicates(true);
}

// Called when the game starts or when spawned
void AShooterHoldableBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShooterHoldableBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AShooterHoldableBase::Equip(const bool bEquip)
{
	bHolding = bEquip;
}

void AShooterHoldableBase::Use(const bool bUse)
{
	if (!bHolding)
	{
		return;
	}
}

void AShooterHoldableBase::OnRep_Holding()
{

}

void AShooterHoldableBase::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	DOREPLIFETIME(AShooterHoldableBase, bHolding);
}