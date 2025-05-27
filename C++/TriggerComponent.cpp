// Fill out your copyright notice in the Description page of Project Settings.


#include "TriggerComponent.h"

UTriggerComponent::UTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


void UTriggerComponent::BeginPlay()
{
	Super::BeginPlay();
    // UE_LOG(LogTemp, Display, TEXT("Trigger Component Alive"));
}

void UTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	// UE_LOG(LogTemp, Display, TEXT("Trigger Component is Ticking: %f"), DeltaTime);

	AActor* Actor = GetAcceptableActor();
	if (Actor != nullptr)
	{
		// UE_LOG(LogTemp, Display, TEXT("Unlocking"));
		UPrimitiveComponent* Component = Cast<UPrimitiveComponent>(Actor->GetRootComponent()); // it will check this component is a primitive component or nullptr
		
		if (Component != nullptr)
		{
			Component->SetSimulatePhysics(false); // To make status drop with Wall
		}
		Actor -> AttachToComponent(this, FAttachmentTransformRules::KeepWorldTransform); // Attach the actor to the trigger component
		Mover->SetShouldMove(true); // Set the mover to move
	}
	else
	{
		// UE_LOG(LogTemp, Display, TEXT("Relocking"));
		Mover->SetShouldMove(false); // Set the mover to move
	}
}

void UTriggerComponent::SetMover(UMover* NewMover)
{
	Mover = NewMover; // name diff name to avoid shadow
}

AActor* UTriggerComponent::GetAcceptableActor() const
{
	TArray<AActor*> Actors;
	GetOverlappingActors(Actors);

	for (AActor* Actor : Actors)
	{
		// FString ActorName = Actor->GetActorNameOrLabel();
		if (Actor -> ActorHasTag(AcceptableActorTag)) // *** need to add tag to Wall
		{
			return Actor;
		};
	}

	return nullptr;
}