// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
// UGameplayStatics include
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"
#include "Engine/DamageEvents.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	SetRootComponent(Root);

	Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

}

void AGun::PullTrigger()
{
	if (CurrentAmmo <= 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("Out of Ammo!"));
		return; // No ammo left, do not fire
	}

	CurrentAmmo--; // Decrease ammo count
	UE_LOG(LogTemp, Warning, TEXT("Ammo left: %d"),CurrentAmmo);
	

	// UE_LOG(LogTemp, Warning, TEXT("Gun Trigger Pulled!"));
	// UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, Mesh->GetSocketLocation(TEXT("MuzzleSocket")), Mesh->GetSocketRotation(TEXT("MuzzleSocket")), true);
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	UGameplayStatics::SpawnSoundAttached(MuzzleSound, Mesh, TEXT("MuzzleFlashSocket"));

	FHitResult Hit;
	FVector ShotDirection;

	bool bSuccess = GunTrace(Hit, ShotDirection);

	if (bSuccess)
	{
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), ImpactSound, Hit.Location);
		
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr); // UDamageType::StaticClass()
			AController* OwnerController = GetOwnerController();
			HitActor->TakeDamage(Damage, DamageEvent, OwnerController, this);
			// UE_LOG(LogTemp, Warning, TEXT("Hit Actor: %s"), *HitActor->GetName());
		}
	};


	// DrawDebugCamera(
	// 	GetWorld(),
	// 	Location,
	// 	Rotation,
	// 	90.f,      // FOV
	// 	2.0f,      // PersistTimeSeconds
	// 	FColor::Red,
	// 	true    // PersistentLines
	// );
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();
	
	CurrentAmmo = MaxAmmo; // Initialize current ammo to max ammo
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	AController* OwnerController = GetOwnerController();
	if (OwnerController == nullptr) 
		return false;
	// Set Location and Roatation
	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint(Location, Rotation);
	ShotDirection = -Rotation.Vector();
	// Draw a debug camera at the gun's location

	FVector End = Location + Rotation.Vector() * MaxRange;
	// Line trace to check for hit
	// FCollisionQueryParams is used to specify parameters for the line trace
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(this); // Ignore the gun itself
	Params.AddIgnoredActor(GetOwner()); // Ignore the owner pawn
	//
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1, Params);
	
}

AController* AGun::GetOwnerController() const
{
	APawn *OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn == nullptr)
		return nullptr;
	return OwnerPawn->GetController();
}