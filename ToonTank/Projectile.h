// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class TOONTANKS_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Combit")
	class UStaticMeshComponent* ProjectileMesh; // Mesh component for the projectile

	UPROPERTY(VisibleAnywhere, Category = "Movement")
	class UProjectileMovementComponent* ProjectileMovementComponent; // Movement component for the projectile

	UFUNCTION()
	void OnHit(
		UPrimitiveComponent* HitComponent, 
		AActor* OtherActor, 
		UPrimitiveComponent* OtherComp, 
		FVector NormalImpulse, 
		const FHitResult& Hit);
	
	UPROPERTY(EditAnywhere)
	float Damage = 20.f; // Damage dealt by the projectile

	UPROPERTY(EditAnywhere, Category = "Combit")
	class UParticleSystem* HitParticles; // Particle effect when the projectile hits something

	UPROPERTY(VisibleAnywhere, Category = "Combit")
	class UParticleSystemComponent* TrailParticles; // Particle effect for the projectile trail

	UPROPERTY(EditDefaultsOnly, Category = "Combit")
	class USoundBase* LaunchSound; // Particle effect when the projectile is destroyed

	UPROPERTY(EditDefaultsOnly, Category = "Combit")
	USoundBase* HitSound; // Sound effect when the projectile hits something
	
	UPROPERTY(EditAnywhere, Category = "Combit")
	TSubclassOf<class UCameraShakeBase> HitCameraShakeClass; // Camera shake effect when the projectile hits something


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
