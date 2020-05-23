
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


void UGrabber::BeginPlay()
{
	Super::BeginPlay();
	SetupInputComponent();
	FindPhysicsHandleComponent();	
}

void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (PhysicsHandle->GrabbedComponent)
	{		
		PhysicsHandle->SetTargetLocation(GetReachLineEnd());
	}
}

//Check if there is a physics handle to use
void UGrabber::FindPhysicsHandleComponent()
{
	if (!PhysicsHandle)
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("%s is missing physics handle"), *GetOwner()->GetName());

	}
}

//Define keys/buttons that are used to activate the Grab and Release functions
void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
	else
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("%s is missing input component"), *GetOwner()->GetName());

	}

	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
}

//Attach the physics handle to the actor the player is looking at
void UGrabber::Grab()
{
	FHitResult HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();

	if (HitResult.GetActor() != nullptr)
	{
		//Attach the physics handle to the thing the player is looking at
		PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), ComponentToGrab->GetOwner()->GetActorRotation());
	}
}

//Release the actor the player is holding
void UGrabber::Release()
{
	PhysicsHandle->ReleaseComponent();
}

//Return the first physics body along the players line of sight
const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	//Ignore the player itself when deciding what's being looked at
	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		viewPointLocation,
		GetReachLineEnd(),
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return HitResult;
}

FVector UGrabber::GetReachLineEnd()
{
	//Where is the player and what are they looking at?
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT viewPointLocation, OUT viewPointRotation);

	//Return a line extending out from the player along their viewing vector
	return viewPointLocation + (viewPointRotation.Vector() * Reach);
}