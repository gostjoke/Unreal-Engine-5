// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Components/CapsuleComponent.h"
#include "BasePawn.generated.h"

UCLASS()
class TOONTANKS_API ABasePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABasePawn();

	void HandleDestruction();
	// virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

protected:
	// Called when the game starts or when spawned
	void RotateTurret(FVector LookAtTarget);
	void Fire();

private:
	// add capsule component for collision
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	class UCapsuleComponent* CapsuleComp; // forwward declaration to eliminate compile mistake
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* BaseMesh; // Mesh for the base of the pawn 坦克底盤
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	UStaticMeshComponent* TurretMesh; // Mesh for the turret of the pawn 坦克炮塔
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components", meta = (AllowPrivateAccess = "true"))
	USceneComponent* ProjectileSpawnPoint; // Mesh for the projectile spawn point 坦克炮塔發射點 是一個 空的場景節點，它本身不會顯示任何模型。

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"), category = "Super Duper Varaibles")
	int32 VisibleAnyWhereInt = 32;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess = "true"),  category = "Super Duper Varaibles")
	int32 EditAnywhereInt = 22;

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	TSubclassOf<class AProjectile> ProjectileClass; // Type of projectile to spawn

	

	UPROPERTY(EditAnywhere,  Category = "Combat")
	class UParticleSystem* DeathParticles; // Particle effect when the pawn is destroyed

	UPROPERTY(EditAnywhere,  Category = "Combat")
	class USoundBase* DeathSound; // Sound effect when the pawn is destroyed

	UPROPERTY(EditAnywhere,  Category = "Combat")
	TSubclassOf<class UCameraShakeBase> DeathCameraShakeClass; // Camera shake effect when the pawn is destroyed
};


