// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/World.h"
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

	UPROPERTY(EditAnywhere, Category = "Config")
	float AcceptanceRadius = 8000.0f;

private:
	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
};
