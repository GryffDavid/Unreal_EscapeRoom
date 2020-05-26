// (C) Copyright Gryffydd David 2019


#include "OpenDoor.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();
	Owner = GetOwner();
}

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	//if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	if (GetTotalMassOfActorsOnPlate() > TriggerMass)
	{
		OnOpenRequest.Broadcast();
	}
	else
	{
		OnCloseRequest.Broadcast();
	}
}

//Returns mass in kg
float UOpenDoor::GetTotalMassOfActorsOnPlate()
{
	float TotalMass = 0.0f;

	//Find all overlapping actors
	if (PressurePlate)
	{
		TArray<AActor*> OverlappingActors;
		PressurePlate->GetOverlappingActors(OUT OverlappingActors);

		for (auto& actor : OverlappingActors)
		{
			TotalMass += actor->FindComponentByClass<UPrimitiveComponent>()->GetMass();
		}
	}

	return TotalMass;
}
