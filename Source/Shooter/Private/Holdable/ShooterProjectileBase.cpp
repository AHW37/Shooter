// Fill out your copyright notice in the Description page of Project Settings.


#include "Holdable/ShooterProjectileBase.h"

// Sets default values
AShooterProjectileBase::AShooterProjectileBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SetReplicates(true);
}

// Called when the game starts or when spawned
void AShooterProjectileBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShooterProjectileBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

