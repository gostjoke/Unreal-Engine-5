// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "Gun.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	Health = MaxHealth; // Initialize health to max health

	Gun = GetWorld()->SpawnActor<AGun>(GunClass);

	// Attach the gun to the character's mesh at the right hand socket
	GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None); // Hide the weapon bone in the mesh
	Gun->AttachToComponent(GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	Gun->SetOwner(this); // Set the owner of the gun to this character
}

bool AShooterCharacter::IsDead() const
{
	return Health <= 0; // Check if health is less than or equal to zero
}


// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent -> BindAxis(TEXT("MoveForward"), this, &AShooterCharacter::MoveForward);
	PlayerInputComponent -> BindAxis(TEXT("LookUp"), this, &APawn::AddControllerPitchInput);
	PlayerInputComponent -> BindAxis(TEXT("MoveRight"), this, &AShooterCharacter::MoveRight); // include A D
	PlayerInputComponent -> BindAxis(TEXT("LookRight"), this, &APawn::AddControllerYawInput); // look right and left 
	PlayerInputComponent -> BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate); // look right and left 
	PlayerInputComponent -> BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate); // look right and left 
	PlayerInputComponent -> BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent -> BindAction("Shoot", IE_Pressed, this, &AShooterCharacter::Shoot);

}

float AShooterCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent, class AController* EventInstigator, AActor* DamageCauser)
{
	float DamageToApply = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	DamageToApply = FMath::Min(Health, DamageToApply); // Ensure we don't apply more damage than current health
	Health -= DamageToApply; // Reduce health by the damage applied
	UE_LOG(LogTemp, Warning, TEXT("Character took damage: %f, Current Health: %f"), DamageToApply, Health);
	
	return DamageToApply; // Return the amount of damage applied

}

void AShooterCharacter::MoveForward(float AxisValue)
{
	AddMovementInput(GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	AddMovementInput(GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
	// Adjust the controller's pitch based on the AxisValue and RotationRate by multiplying by DeltaTime
	AddControllerPitchInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());

}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	AddControllerYawInput(AxisValue * RotationRate * GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::Shoot()
{
	Gun -> PullTrigger(); // Call the PullTrigger method on the Gun instance
}