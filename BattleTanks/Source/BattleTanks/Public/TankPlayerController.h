// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Tank.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class BATTLETANKS_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATankPlayerController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

	void AimTowardsCrosshair();

	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	bool GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	float CrosshairXLocation = .5f;

	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "UI")
	float CrosshairYLocation = .33333f;

	float LineTraceRange = 1000000.0f;

protected:
	UFUNCTION(BlueprintCallable)
	ATank* GetControlledTank() const;
};
