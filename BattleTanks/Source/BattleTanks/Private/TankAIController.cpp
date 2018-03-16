// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

ATankAIController::ATankAIController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	APawn* Tank = GetPawn();
	APawn* PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

	UTankAimingComponent* AimingComponent = Cast<UTankAimingComponent>(Tank->GetComponentByClass(UTankAimingComponent::StaticClass()));

	if (!ensure(PlayerTank && AimingComponent)) { return; }
	
	//Move towards player
	MoveToActor(PlayerTank, AcceptanceRadius);

	//Aim towards player
	AimingComponent->AimAt(PlayerTank->GetActorLocation());

	//Fire at player if locked
	//TODO confirm that the state is Locked
	if (AimingComponent->GetFiringState() == EFiringState::Locked)
	{
		AimingComponent->Fire();
	}
}
