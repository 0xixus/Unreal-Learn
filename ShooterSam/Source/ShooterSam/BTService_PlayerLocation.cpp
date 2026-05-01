// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocation.h"

#include "ShooterAI.h"
#include "BehaviorTree/BlackboardComponent.h"

UBTService_PlayerLocation::UBTService_PlayerLocation()
{
	NodeName = TEXT("Get Player Location");
}

void UBTService_PlayerLocation::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AShooterAI* OwnerController = Cast<AShooterAI>(OwnerComp.GetAIOwner());
	AShooterSamCharacter* Player = OwnerController ? OwnerController->PlayerCharacter : nullptr;
	UBlackboardComponent* Blackboard = OwnerController ? OwnerController->GetBlackboardComponent() : nullptr;
	
	if (Player && Blackboard)
	{
		Blackboard->SetValueAsVector(GetSelectedBlackboardKey(), Player->GetActorLocation());
	}
}
