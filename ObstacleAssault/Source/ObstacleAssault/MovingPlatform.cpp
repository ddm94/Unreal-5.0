// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();

	StartLocation = GetActorLocation();
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	
	Super::Tick(DeltaTime);
	
	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}

void AMovingPlatform::MovePlatform(float DeltaTime)
{
	// Send platform back if gone too far
		// Check how far we've moved
		// Reverse direction of motion if gone too far
	if (ShouldPlatformReturn())
	{
		// Debugging 
		/*
		float DistanceMoved = FVector::Distance(StartLocation, GetActorLocation());
		float OverShot = DistanceMoved - MoveDistance;
		FString Name = GetName();
		UE_LOG(LogTemp, Display, TEXT("%s overshot by: %f"), *Name, OverShot);
		*/

		FVector MoveDirection = PlatformVelocity.GetSafeNormal();

		// We want to move exactly to the end and no farther
		StartLocation += MoveDirection * MoveDistance;

		// Move to the end location otherwise the platform will have overshot and gone past that end location
		SetActorLocation(StartLocation);

		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		// Move platform forwards
			// Get current location (local variable)
		FVector CurrentLocation = GetActorLocation();
			// Add vector to that location
		CurrentLocation += PlatformVelocity * DeltaTime;
			// Set the location
		SetActorLocation(CurrentLocation);
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime)
{
	//UE_LOG(LogTemp, Display, TEXT("%s Rotating..."), *GetName());

	AddActorLocalRotation(RotationVelocity * DeltaTime);
}

bool AMovingPlatform::ShouldPlatformReturn() const
{
	return GetDistanceMoved() > MoveDistance;
}

float AMovingPlatform::GetDistanceMoved() const
{
	return FVector::Distance(StartLocation, GetActorLocation());
}