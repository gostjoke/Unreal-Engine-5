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
	// UE_LOG(LogTemp, Warning, TEXT("Gun Trigger Pulled!"));
	// UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), MuzzleFlash, Mesh->GetSocketLocation(TEXT("MuzzleSocket")), Mesh->GetSocketRotation(TEXT("MuzzleSocket")), true);
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, Mesh, TEXT("MuzzleFlashSocket"));

	APawn* OwnerPawn = Cast<APawn>(GetOwner());
	if (OwnerPawn==nullptr) return;
	AController* OwnerController = OwnerPawn -> GetController();
	if (OwnerController == nullptr) return;
	// Set Location and Roatation
	FVector Location;
	FRotator Rotation;

	OwnerController->GetPlayerViewPoint(Location, Rotation);
	// Draw a debug camera at the gun's location

	FVector End = Location + Rotation.Vector() * MaxRange;
	// Line trace to check for hit

	FHitResult Hit;
	bool bSuccess = GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECollisionChannel::ECC_GameTraceChannel1);
	if (bSuccess)
	{
		FVector ShotDirection = -Rotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), ImpactEffect, Hit.Location, ShotDirection.Rotation());
		
		AActor* HitActor = Hit.GetActor();
		if (HitActor != nullptr)
		{
			FPointDamageEvent DamageEvent(Damage, Hit, ShotDirection, nullptr); // UDamageType::StaticClass()
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
	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

