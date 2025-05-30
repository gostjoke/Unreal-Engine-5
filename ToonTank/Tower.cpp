// Fill out your copyright notice in the Description page of Project Settings.


#include "Tower.h"
#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

ATower::ATower()
{
    // 可留空或加入初始化邏輯
}


void ATower::Tick(float DeltaTime) 
{
    Super::Tick(DeltaTime);

    // find distance to the tank
    float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());

    // if the tank is within range, rotate turret to face the tank
    if (InFireRange())
    {
        RotateTurret(Tank->GetActorLocation());
    }
}

void ATower::BeginPlay()
{
    Super::BeginPlay();
    // Additional initialization code for the tower can go here
    // For example, setting up initial state or binding events
    Tank = Cast<ATank>(UGameplayStatics::GetPlayerPawn(this, 0)); // Get the player tank

    GetWorldTimerManager().SetTimer(
        FireRateTimerHandle, 
        this, 
        &ATower::CheckFireCondition, 
        FireRate, 
        true // Looping
        // 0.f // Initial delay
    );
}   

void ATower::CheckFireCondition()
{
    if (InFireRange())
    {
        Fire();
    }

}

bool ATower::InFireRange()
{
    if (Tank)
    {
        float Distance = FVector::Dist(GetActorLocation(), Tank->GetActorLocation());
        return Distance <= FireRange;
    }
    return false; // If no tank is found, return false
}