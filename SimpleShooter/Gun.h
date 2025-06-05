// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"


UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	void PullTrigger();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* MuzzleFlash; // Particle system for muzzle flash 槍口火焰

	UPROPERTY(EditAnywhere)
	class UParticleSystem* ImpactEffect; // Particle system for impact effect 子彈擊中效果

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.0f; // Maximum range of the gun

	UPROPERTY(EditAnywhere)
	float Damage = 20.0f; // Damage dealt by the gun
};
