// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ShooterHoldableBase.generated.h"

UCLASS()
class SHOOTER_API AShooterHoldableBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AShooterHoldableBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Equip(const bool bEquip);

	UFUNCTION(BlueprintCallable, Category = Holdable)
	virtual void Use(const bool bUse);

	UFUNCTION()
	void OnRep_Holding();
private:
	UPROPERTY(Replicated, ReplicatedUsing = OnRep_Holding)
	bool bHolding;
};
