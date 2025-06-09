// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
    Super::PawnKilled(PawnKilled); // Call the base class implementation

    // Check if the killed pawn is a player character

    // UE_LOG(LogTemp, Warning, TEXT("A pawn has been killed!"));
    APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());

    if (PlayerController != nullptr)
    {
        // PlayerController->GameHasEnded(nullptr, false); // End the game for the player
        EndGame(false); // Call the EndGame function with false indicating player loss
    }

    // For loop over ShooterAI in World:
        // Is not dead?
            // return 
    for (AShooterAIController* Controller : TActorRange<AShooterAIController>(GetWorld()))
    {
        if (!Controller->IsDead())
        {
            return; // If any AI is still alive, do not end the game
        }
    }

    EndGame(true);
    // End game
    
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
    for (AController* Controller : TActorRange<AController>(GetWorld()))
    {
        bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
        Controller->GameHasEnded(Controller->GetPawn(), bIsWinner); // Notify each controller about the end of the game
    };
}