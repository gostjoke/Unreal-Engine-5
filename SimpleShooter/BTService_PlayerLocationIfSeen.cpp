// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Pawn.h"
#include "AIController.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
    NodeName = "Update Player Location If Seen";
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent &OwnerComp, uint8 *NodeMemory, float DeltaSeconds)
{
    Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

    APawn *PlayerPawn = UGameplayStatics::GetPlayerPawn(OwnerComp.GetWorld(), 0);

    if (PlayerPawn == nullptr)
    {
        return; // If PlayerPawn is not valid, exit the function
    }

    if (OwnerComp.GetAIOwner() == nullptr)
    {
        // If the AI does not have line of sight to the player, do not update the location
        return;
    }

    if (OwnerComp.GetAIOwner()->LineOfSightTo(PlayerPawn))
    {
        // If the AI does not have line of sight to the player, do not update the location
        OwnerComp.GetBlackboardComponent()->SetValueAsVector(GetSelectedBlackboardKey(), PlayerPawn->GetActorLocation());
    }
    else
    {
        // If the AI does not have line of sight to the player, clear the location
        OwnerComp.GetBlackboardComponent()->ClearValue(GetSelectedBlackboardKey());
    }


}