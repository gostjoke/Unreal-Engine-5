// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"
#include "Components/StaticMeshComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "GameFramework/DamageType.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
// Sets default values
AProjectile::AProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // dont need any tick
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Projectile Mesh"));
	RootComponent = ProjectileMesh; // Set the root component to the projectile mesh

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("Projectile Movement Component"));
	ProjectileMovementComponent->InitialSpeed = 1300.f; // Set initial speed of the projectile
	ProjectileMovementComponent->MaxSpeed = 1300.f; // Set maximum speed of the projectile

	TrailParticles = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Projectile Trail"));
	TrailParticles->SetupAttachment(RootComponent); // Attach the particle system component to the root component
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();

	ProjectileMesh->OnComponentHit.AddDynamic(this, &AProjectile::OnHit); // Bind the OnHit function to the OnComponentHit event

	if (LaunchSound) 
	{
		UGameplayStatics::PlaySoundAtLocation(
			this, 
			LaunchSound, 
			GetActorLocation()
		); // Play the launch sound at the projectile's location
	};
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnHit(UPrimitiveComponent *HitComp, AActor *OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	auto MyOwner = GetOwner();
	if (MyOwner == nullptr) 
	{
		Destroy(); // If there is no owner, destroy the projectile
		return; // If there is no owner, do nothing
	}
	auto MyOwnerInstigator = MyOwner-> GetInstigatorController();
	auto DamageTypeClass = UDamageType::StaticClass();

	if (OtherActor && OtherActor != this && OtherActor != MyOwner)
	{
		// Apply damage to the hit actor
		UGameplayStatics::ApplyDamage(OtherActor, Damage, MyOwnerInstigator, this, DamageTypeClass);
		if(HitParticles){
			UGameplayStatics::SpawnEmitterAtLocation(
			this, 
			HitParticles, 
			GetActorLocation(), 
			GetActorRotation()
			); // Spawn hit particles at the location of the hit
		}
		// Optionally, you can destroy the projectile after hitting something
		if (HitSound)
		{
			UGameplayStatics::PlaySoundAtLocation(
				this, 
				HitSound, 
				GetActorLocation() // Play the hit sound at the projectile's location
			);
		}
		if (HitCameraShakeClass)
		{
			GetWorld()->GetFirstPlayerController()->ClientStartCameraShake(HitCameraShakeClass); // Play camera shake effect
		}

	};

	Destroy();

}