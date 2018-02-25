// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	AProjectile();

	void LaunchProjectile(float Speed);

protected:
	virtual void BeginPlay() override;

	UProjectileMovementComponent* ProjectileMovement = nullptr;

public:	
	virtual void Tick(float DeltaTime) override;
	
};
