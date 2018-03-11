// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();

	//Overlap hit method
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::ApplySidewaysForce()
{
	float SlippageSpeed = FVector::DotProduct(GetRightVector(), GetComponentVelocity());

	float DeltaTime = GetWorld()->GetDeltaSeconds();
	FVector CorrectionAcceleration = -SlippageSpeed / DeltaTime * GetRightVector();

	UStaticMeshComponent* TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	FVector CorrectionForce = (TankRoot->GetMass() * CorrectionAcceleration) / 2; //Two tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTrack::SetThrottle(float Throttle)
{
	CurrentThrottle = FMath::Clamp<float>(CurrentThrottle + Throttle, -1, 1);
}

void UTankTrack::DriveTrack()
{
	//UE_LOG(LogTemp, Warning, TEXT("%s: %s throttle at %f"), *GetOwner()->GetName(), *GetName(), CurrentThrottle);

	FVector ForceApplied = GetForwardVector() * CurrentThrottle * TrackMaxDrivingForce;
	FVector ForceLocation = GetComponentLocation();
	UPrimitiveComponent* TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit)
{
	if (!IsAboveSpeed())
	{
		DriveTrack();

		ApplySidewaysForce();
	}
	CurrentThrottle = 0;
}

bool UTankTrack::IsAboveSpeed()
{
	FVector Velocity = GetOwner()->GetVelocity();
	float Speed = Velocity.Size();

	if (Speed > MaxSpeed)
	{
		return true;
	}
	else
	{
		return false;
	}
}
