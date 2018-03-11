// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"

UTankAimingComponent::UTankAimingComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankAimingComponent::BeginPlay()
{
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	if (!DoesHaveAmmo())
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds)
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}

bool UTankAimingComponent::DoesHaveAmmo()
{
	return (CurrentAmmo > 0);
}

void UTankAimingComponent::Initialize(UTankBarrel* BarrelToSet, UTankTurret* TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation)
{
	if (!ensure(Barrel)) { return; }

	FVector OutLaunchVelocity;
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(this, OutLaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveAimSolution)
	{
		AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	if (!ensure(Barrel && Turret)) { return; }

	FRotator BarrelRotation = Barrel->GetForwardVector().Rotation();
	FRotator AimAsRotation = AimDirection.Rotation();
	FRotator DeltaRotation = AimAsRotation - BarrelRotation;

	Barrel->Elevate(DeltaRotation.Pitch);

	if (FMath::Abs(DeltaRotation.Yaw) < 180) 
	{
		Turret->Rotate(DeltaRotation.Yaw);
	} 
	else
	{
		Turret->Rotate(-DeltaRotation.Yaw);
	}
	
}

void UTankAimingComponent::Fire()
{
	if (FiringState == EFiringState::Locked || FiringState == EFiringState::Aiming)
	{
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }

		FTransform Transform = Barrel->GetSocketTransform(FName("Projectile"));

		AProjectile* Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint.Get(),
			Transform.GetLocation(),
			Transform.GetRotation().Rotator()
			);

		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();

		CurrentAmmo--;
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	if (!ensure(Barrel)) { return false; }
	auto BarrelForward = Barrel->GetForwardVector();
	return !BarrelForward.Equals(AimDirection, 0.01); // vectors are equal
}

EFiringState UTankAimingComponent::GetFiringState() const
{
	return FiringState;
}

int32 UTankAimingComponent::GetAmmo() const
{
	return CurrentAmmo;
}