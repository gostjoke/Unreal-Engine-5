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

	FString Name = GetName(); 
	
	UE_LOG(LogTemp, Display, TEXT("BeginPlay: %s"), *Name);
	// UE_LOG(LogTemp, Warning, TEXT("Your message"));
	// UE_LOG(LogTemp, Error, TEXT("Your message"));
}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	MovePlatform(DeltaTime);
	RotatePlatform(DeltaTime);
}


void AMovingPlatform::MovePlatform(float DeltaTime) // A prase it is actor
{
	// Reverse direction of motion if too far
	if (ShouldPlatformReturn()) {
	
		// Temporary for log name
		// float OverShoot = DistanceMoved - MoveDistance;
		// FString Name = GetName();
		// UE_LOG(LogTemp, Display, TEXT("%s Platform Overshoot by %f"), *Name, OverShoot);
		
		FVector MoveDirection = PlatformVelocity.GetSafeNormal();
		// Get the distance to move back
		StartLocation = StartLocation + MoveDirection * MoveDistance;
		// Set the new location	
		SetActorLocation(StartLocation);
		PlatformVelocity = -PlatformVelocity;
	}
	else
	{
		// Move platform forward
			// Get Current Location
		FVector CurrentLocation = GetActorLocation();
			// Add vector to the location
		CurrentLocation += (PlatformVelocity * DeltaTime);
			// Set the location
		SetActorLocation(CurrentLocation);
		// Send Platform back if gone too far
	}
}

void AMovingPlatform::RotatePlatform(float DeltaTime) // DT == DeltaTime
{

	AddActorLocalRotation(RotationVelocity * DeltaTime);
}


bool AMovingPlatform::ShouldPlatformReturn() const
{
	// Check how far we've moved
	return GetDistanceMoved() > MoveDistance;
}


float AMovingPlatform::GetDistanceMoved() const
{
	// Get the distance moved
	return FVector::Dist(StartLocation, GetActorLocation());
}