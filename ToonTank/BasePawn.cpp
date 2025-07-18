// Fill out your copyright notice in the Description page of Project Settings.


#include "BasePawn.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
// #include "DrawDebugHelpers.h"
#include "Projectile.h"
#include "kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ABasePawn::ABasePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// RootComponent;
	CapsuleComp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Collider"));
	RootComponent = CapsuleComp;

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Base Mesh"));
	BaseMesh->SetupAttachment(CapsuleComp);

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BaseMesh);

	ProjectileSpawnPoint = CreateDefaultSubobject<USceneComponent>(TEXT("Spawn Point"));
	ProjectileSpawnPoint->SetupAttachment(TurretMesh);
}

void ABasePawn::HandleDestruction()
{
	// TODO: Visual and sound effects for destruction
	if (DeathParticles)
	{
		// Spawn death particles at the pawn's location
		UGameplayStatics::SpawnEmitterAtLocation(
			this, 
			DeathParticles, 
			GetActorLocation(), 
			GetActorRotation()
		);
	}
	if (DeathSound)
	{
		// Play death sound at the pawn's location
		UGameplayStatics::PlaySoundAtLocation(
			this, 
			DeathSound, 
			GetActorLocation()
		);
	}
	if (DeathCameraShakeClass)
	{
		GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(DeathCameraShakeClass); // Play camera shake effect
	}
}

void ABasePawn::RotateTurret(FVector LookAtTarget)
{
	FVector ToTarget = LookAtTarget - TurretMesh->GetComponentLocation();
	FRotator LookAtRotation = FRotator(0.f, ToTarget.Rotation().Yaw, 0.f); // Normalize the rotation to avoid any issues with large angles
	// UGameplayStatics::GetWorldDeltaSeconds(this) almost equal GetWorld()->GetDeltaSeconds()
	TurretMesh->SetWorldRotation(
		FMath::RInterpTo(TurretMesh->GetComponentRotation(), 
		LookAtRotation, 
		UGameplayStatics::GetWorldDeltaSeconds(this), 
		5.f));
}

void ABasePawn::Fire()
{
	// Implement firing logic here
	// For example, spawn a projectile at the ProjectileSpawnPoint location
	// UE_LOG(LogTemp, Warning, TEXT("Fire function called!"));

	FVector Location = ProjectileSpawnPoint->GetComponentLocation();
	FRotator Rotation = ProjectileSpawnPoint->GetComponentRotation();
	
	auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileClass, Location, Rotation);
	Projectile->SetOwner(this); // Set the owner of the projectile to this pawn
	// DrawDebugSphere(
	// 	GetWorld(),
	// 	Location, // Offset the sphere a bit above the tank
	// 	25.f, // Radius of the sphere
	// 	12, // Segments
	// 	FColor::Red,
	// 	false,
	// 	3.f
	// );

	
}