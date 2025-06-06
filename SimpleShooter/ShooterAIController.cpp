// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
    Super::BeginPlay();
}

void AShooterAIController::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
    // Additional AI controller initialization can be done here
    APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(GetWorld(), 0);

    // If LineOfSight 
        // MoveTo
        // SetFocus
    //else
        // ClearFocus
        // StopMovement
    if (LineOfSightTo(PlayerPawn))
    {
        SetFocus(PlayerPawn); // Set focus on the player pawn
        MoveToActor(PlayerPawn, AcceptanceRadius); // Move towards the player pawn with a specified acceptance radius
    }
    else
    {
        ClearFocus(EAIFocusPriority::Gameplay); // Clear focus if not in line of sight
        StopMovement(); // Stop movement if not in line of sight
    }
}