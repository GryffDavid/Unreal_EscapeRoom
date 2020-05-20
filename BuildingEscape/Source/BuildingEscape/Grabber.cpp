
// (C) Copyright Gryffydd David 2019


#include "Grabber.h"
#include "GameFramework/Actor.h"
#include "GameFramework/PlayerController.h"

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

	// ...
	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty"));
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
	
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT viewPointLocation, OUT viewPointRotation);

	UE_LOG(LogTemp, Warning, TEXT("Location: %s, Rotation: %s"), *viewPointLocation.ToString(), *viewPointRotation.ToString());

	FVector LineTraceEnd = viewPointLocation + (viewPointRotation.Vector() * Reach);
	DrawDebugLine(GetWorld(), viewPointLocation, LineTraceEnd, FColor().Red);


	//Setup query parameters
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult, 
		viewPointLocation, 
		LineTraceEnd, 
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), 
		TraceParams
	);

	AActor* ActorHit = HitResult.GetActor();
	if (ActorHit)
	{
		UE_LOG(LogTemp, Warning, TEXT("Looking at: %s"), *(ActorHit->GetName()));
	}
}

