// Fill out your copyright notice in the Description page of Project Settings.

#include "Projectile.h"
#include "Engine/World.h"

AProjectile::AProjectile()
{
	PrimaryActorTick.bCanEverTick = true;

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(FName("Aiming Component"));
	ProjectileMovement->bAutoActivate = false;
}

void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AProjectile::LaunchProjectile(float Speed)
{
	UE_LOG(LogTemp, Warning, TEXT("%f: Tank fires at %f speed"), GetWorld()->GetTimeSeconds(), Speed);

	ProjectileMovement->SetVelocityInLocalSpace(FVector::ForwardVector * Speed);
	ProjectileMovement->Activate();
}

