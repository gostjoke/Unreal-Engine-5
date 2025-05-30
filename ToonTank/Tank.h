// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tank.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATank : public ABasePawn
{
	GENERATED_BODY()

public:
	ATank();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Handle destruction of the tank
	void HandleDestruction();

	APlayerController* GetTankPlayerController() const { return TankPlayerController; } // Getter for the player controller

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private: 

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class USpringArmComponent* SpringArm; // Spring Arm Component for camera

	UPROPERTY(VisibleAnywhere, Category = "Components")
	class UCameraComponent* Camera; // Camera Component for the tank

	UPROPERTY(EditAnywhere, Category = "Movement")
	float Speed = 400.f;

	UPROPERTY(EditAnywhere, Category = "Movement")
	float TurnRate = 45.f; // Speed of turning the tank

	void Move(float Value);
	void Turn(float Value);

	APlayerController* TankPlayerController; // Reference to the player controller
};

