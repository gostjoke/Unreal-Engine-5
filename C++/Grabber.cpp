// Fill out your copyright notice in the Description page of Project Settings.


#include "Grabber.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
// #include "PhysicsEngine/PhysicsHandleComponent.h"

// Sets default values for this component's properties
UGrabber::UGrabber()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called when the game starts
void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	// Remeber to set the Object collision to overlap
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Physics Handle found"));
		return;
	}

	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		// If we are holding something, update its position
		FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance; // Adjust the hold distance as needed
		PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	}
	// Get Target Rotation
	FVector TargetLocation = GetComponentLocation() + GetForwardVector() * HoldDistance; // Adjust the hold distance as needed
	PhysicsHandle->SetTargetLocationAndRotation(TargetLocation, GetComponentRotation());
	// ...
	
	// FRotator MyRotation = GetComponentRotation();
	// FString RotationString = MyRotation.ToCompactString();
	// UE_LOG(LogTemp, Warning, TEXT("Grabber Rotation: %s"), *RotationString);

	// float Time = GetWorld() -> TimeSeconds;
	// UE_LOG(LogTemp, Display, TEXT("Current Time: %f"), Time);

	// DrawDebugLine

		// float Damage = 0;
	// if (HasDamage(Damage)){
	// 	PrintDamage(Damage);
	// };
	// float& DamageRef = Damage; // Create a reference to the Damage variable
	
	// UE_LOG(LogTemp, Warning, TEXT("Damage Reference: %f"), DamageRef);


}

void UGrabber::Grab() // ctril + shift + B + CrytalRaiderEdiot win64 Develpment Build
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Physics Handle found"));
		return;
	}

	FHitResult HitResult;
	bool HasHit = GetGrabbableInReach(HitResult); // Check if we hit something in reach
	
	if (HasHit)
	{
		UPrimitiveComponent* HitComponent = HitResult.GetComponent();
		HitComponent -> WakeAllRigidBodies(); // Wake up the rigid body if it is asleep
		HitResult.GetActor()->Tags.Add("Grabbed"); // Add a tag to the actor for identification
		PhysicsHandle->GrabComponentAtLocationWithRotation(
			HitResult.GetComponent(), // The component that was hit
			NAME_None, // No specific bone name
			HitResult.ImpactPoint, // The location where the hit occurred
			GetComponentRotation() // The rotation of the impact normal
		);
		// AActor* HitActor = HitResult.GetActor();
		// UE_LOG(LogTemp, Display, TEXT("Hit actor: %s"), *HitActor->GetActorNameOrLabel());
	}
}

void UGrabber::Release() // ctril + shift + B + CrytalRaiderEdiot win64 Develpment Build
{
	UPhysicsHandleComponent* PhysicsHandle = GetPhysicsHandle();
	if (PhysicsHandle == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Physics Handle found"));
		return;
	}

	if (PhysicsHandle->GetGrabbedComponent() != nullptr)
	{
		AActor* GrabbedActor = PhysicsHandle->GetGrabbedComponent()->GetOwner();;
		GrabbedActor->Tags.Remove("Grabbed");
		PhysicsHandle->ReleaseComponent(); // Release the grabbed component

		 // Remove the tag from the actor
		UE_LOG(LogTemp, Warning, TEXT("Released Grab"));
	}

}	

UPhysicsHandleComponent* UGrabber::GetPhysicsHandle() const
{
	UPhysicsHandleComponent* Result = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (Result == nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Grabber: No Physics Handle found on owner %s"), *GetOwner()->GetName());
	}
	
	return Result;
}

bool UGrabber::GetGrabbableInReach(FHitResult& OutHitResult) const
{
	FVector Start = GetComponentLocation();
	FVector End = Start + GetForwardVector() * MaxGrabDistance; // 100 units forward from the component's location
	DrawDebugLine(GetWorld(), Start, End, FColor::Red);
	DrawDebugSphere(GetWorld(), End, 10,10, FColor::Blue, false, 5); // Draw a sphere at the start location

	FCollisionShape Sphere = FCollisionShape::MakeSphere(GrabRadius); // Create a sphere shape with the specified radius
	FHitResult HitResult;
	return GetWorld()->SweepSingleByChannel(
		OutHitResult,
		Start, End,
		FQuat::Identity,
		ECC_GameTraceChannel2,
		Sphere
	); // see config DefaultEngine.ini Grabber

}

// void UGrabber::PrintDamage(const float& Damage)
// {	
// 	UE_LOG(LogTemp, Warning, TEXT("Damage: %f"), Damage);
// }

// bool UGrabber::HasDamage(float& OutDamage)
// {
// 	// OutDamage = 100.0f; // Example damage value
// 	return true;
// }	
