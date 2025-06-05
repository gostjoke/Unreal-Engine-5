// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun; // Forward declaration of the Gun class

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	UFUNCTION(BlueprintPure)
	bool IsDead() const; // Pure Node means no execution pin

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser) override;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);
	void LookUpRate(float AxisValue);
	void LookRightRate(float AxisValue);
	void Shoot(); // Function to handle shooting

	// Add other member variables and functions as needed

	UPROPERTY(EditAnywhere)
	float RotationRate = 10.0f; // Rotation rate for the character

	UPROPERTY(EditAnywhere)
	float MaxHealth = 100; 

	UPROPERTY(VisibleAnywhere)
	float Health; // Current health of the character

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunClass; // Class of the gun to spawn

	UPROPERTY()
	AGun* Gun; // Instance of the gun, Actual Gun
};
