// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BasePawn.h"
#include "Tower.generated.h"

/**
 * 
 */
UCLASS()
class TOONTANKS_API ATower : public ABasePawn
{
	GENERATED_BODY()
	
public:
	// Sets default values for this pawn's properties
	virtual void Tick(float DeltaTime) override;
	ATower();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	class ATank* Tank; // Reference to the target tank

	UPROPERTY(EditDefaultsOnly, Category = "Combat")
	float FireRange = 300.f; // Range within which the tower can attack the tank

	FTimerHandle FireRateTimerHandle;
	float FireRate = 2.f; // Time between attacks
	void CheckFireCondition(); // Function to check if the tower can fire at the tank

	bool InFireRange(); 
};
