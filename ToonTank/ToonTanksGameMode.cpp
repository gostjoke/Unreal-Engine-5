// Fill out your copyright notice in the Description page of Project Settings.


#include "ToonTanksGameMode.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "Tower.h"
#include "ToonTanksPlayerController.h"

void AToonTanksGameMode::ActorDied(AActor* DeadActor)
{
    if (DeadActor == Tank)
    {
        Tank->HandleDestruction(); // Call the tank's destruction handling
        if(ToonTanksPlayerController)
        {
            ToonTanksPlayerController->SetPlayerEnabledState(false); // Disable player input
        }
    }
    else if (ATower* DestroyedTower = Cast<ATower>(DeadActor))
    {
        DestroyedTower->HandleDestruction();
    }
    else
    {
        // Handle other actors' deaths if necessary
        UE_LOG(LogTemp, Warning, TEXT("An actor has died: %s"), *DeadActor->GetName());
    }
}

void AToonTanksGameMode::BeginPlay()
{
    Super::BeginPlay();

    HandleGameStart();
    // Initialize the player tank reference


}

void AToonTanksGameMode::HandleGameStart()
{
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0));
    ToonTanksPlayerController = Cast<AToonTanksPlayerController>(UGameplayStatics::GetPlayerController(this, 0));

    if (ToonTanksPlayerController)
    {
        ToonTanksPlayerController->SetPlayerEnabledState(false); // Disable player input initially

        FTimerHandle PlayEnableTimerHandle; // Timer handle for enabling player input
        FTimerDelegate PlayEnableTimerDelegate = FTimerDelegate::CreateUObject(
            ToonTanksPlayerController, 
            &AToonTanksPlayerController::SetPlayerEnabledState, 
            true // Enable player input
        );
        GetWorld()->GetTimerManager().SetTimer(
            PlayEnableTimerHandle, // Timer handle to manage the timer
            PlayEnableTimerDelegate,  // Delegate to call when the timer expires
            StartDelay, // Time to wait before enabling player input 3 secs
            false // Only execute once
        );
    }
}