// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/ShooterCharacterBase.h"

// Sets default values
AShooterCharacterBase::AShooterCharacterBase()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FP_MeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("FP_MeshComponent"));
	FP_MeshComponent->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepRelativeTransform);
	FP_MeshComponent->SetOnlyOwnerSee(true);
	FP_MeshComponent->SetOwnerNoSee(false);	

	// Setup TP_Mesh
	GetMesh()->bOwnerNoSee = true;
	GetMesh()->bOnlyOwnerSee = false;
	GetMesh()->bReceivesDecals = false;
}

// Called when the game starts or when spawned
void AShooterCharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShooterCharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

bool AShooterCharacterBase::IsFirstPerson() const
{
	return Controller && Controller->IsLocalPlayerController();
}

