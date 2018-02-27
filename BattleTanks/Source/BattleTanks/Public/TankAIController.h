// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "AIController.h"
#include "TankAimingComponent.h"
#include "TankAIController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankAIController : public AAIController
{
	GENERATED_BODY()

public:
	ATankAIController();

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	float AcceptanceRadius = 3000.0f;
};
