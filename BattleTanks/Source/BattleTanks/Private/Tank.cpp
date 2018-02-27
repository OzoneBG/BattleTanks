// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "Engine/World.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();

	TankAimingComponent = Cast<UTankAimingComponent>(GetComponentByClass(UTankAimingComponent::StaticClass()));
}

void ATank::AimAt(FVector HitLocation)
{
	if (!ensure(TankAimingComponent)) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}

void ATank::Fire()
{
	if (!ensure(Barrel)) { return; }

	bool bIsReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (bIsReloaded)
	{
		FTransform Transform = Barrel->GetSocketTransform(FName("Projectile"));

		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint.Get(),
			Transform.GetLocation(),
			Transform.GetRotation().Rotator()
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
	}
}
