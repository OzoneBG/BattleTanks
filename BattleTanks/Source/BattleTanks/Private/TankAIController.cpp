// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

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

	ATank* Tank = Cast<ATank>(GetPawn());

	if (Tank)
	{
		ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (PlayerTank)
		{
			Tank->AimAt(PlayerTank->GetActorLocation());

			Tank->Fire();
		}
	}
}