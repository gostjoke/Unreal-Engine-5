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

    // IE_Pressed means the action is triggered when the key is pressed down
    PlayerInputComponent->BindAction(TEXT("Fire"), IE_Pressed, this, &ATank::Fire); // This is for moving up and down
}

void ATank::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (TankPlayerController)
    {
        FHitResult HitResult;
        TankPlayerController->GetHitResultUnderCursor(
            ECollisionChannel::ECC_Visibility, 
            false, 
            HitResult);
        
        // DrawDebugSphere(
        //     GetWorld(),
        //     HitResult.ImpactPoint, // Offset the sphere a bit above the tank
        //     25.f, // Radius of the sphere
        //     12, // Segments
        //     FColor::Red,
        //     false,
        //     -1.f
        // );   
        
        RotateTurret(HitResult.ImpactPoint); // Rotate the turret to face the hit point
        
    }
}

void ATank::HandleDestruction()
{
    Super::HandleDestruction();
    SetActorHiddenInGame(true); // Hide the tank when it is destroyed

    SetActorTickEnabled(false); // Disable ticking for the tank when it is destroyed
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();

    // Gained access to the Controller
    // Cast from AController* to APlayerController*
    // Now we can access APlayerController::GetHitResultUnderCursor()
    TankPlayerController = Cast<APlayerController>(GetController());
	
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