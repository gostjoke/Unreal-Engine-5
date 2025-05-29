// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "Kismet/GameplayStatics.h"


ATank::ATank()
{
    SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
    SpringArm->SetupAttachment(RootComponent);

    // Camerea
    Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
    Camera->SetupAttachment(SpringArm);

    // Set the spring arm length
}

void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    UE_LOG(LogTemp, Warning, TEXT("SetupPlayerInputComponent called!"));
    // Bind movement input
    PlayerInputComponent->BindAxis(TEXT("MoveForward"), this, &ATank::Move);
    PlayerInputComponent->BindAxis(TEXT("Turn"), this, &ATank::Turn);
}

void ATank::Move(float Value)
{
    // UE_LOG(LogTemp, Warning, TEXT("Move called with Value: %f"), Value);
    FVector DeltaLocation = FVector::ZeroVector; // [0, 0, 0]

    // X = Value * DeltaTime * Speed;
    DeltaLocation.X = Value * Speed * UGameplayStatics::GetWorldDeltaSeconds(this); //

    AddActorLocalOffset(DeltaLocation, true); // true means sweep, it will check for collisions
}

void ATank::Turn(float Value)
{
    FRotator DeltaRotation = FRotator::ZeroRotator; // [0, 0, 0]
    // Yaw = Value * DeltaTime * TurnRate;
    DeltaRotation.Yaw = Value * TurnRate * UGameplayStatics::GetWorldDeltaSeconds(this); // 0.0166667f;
    // add to actor
    AddActorLocalRotation(DeltaRotation, true); // true means sweep, it will check for collisions
    
}