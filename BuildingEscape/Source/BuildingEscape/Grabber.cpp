
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

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT viewPointLocation, OUT viewPointRotation);
	FVector LineTraceEnd = viewPointLocation + (viewPointRotation.Vector() * Reach);

	if (PhysicsHandle->GrabbedComponent)
	{		
		PhysicsHandle->SetTargetLocation(LineTraceEnd);
	}
}


void UGrabber::FindPhysicsHandleComponent()
{
	if (PhysicsHandle)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Physics handle for %s found: %s"), *GetOwner()->GetName(), *PhysicsHandle->GetName());
	}
	else
	{
		UE_LOG(
			LogTemp,
			Error,
			TEXT("%s is missing physics handle"), *GetOwner()->GetName());

	}
}

void UGrabber::SetupInputComponent()
{
	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();

	if (InputComponent)
	{
		UE_LOG(
			LogTemp,
			Warning,
			TEXT("Input component for %s found: %s"), *GetOwner()->GetName(), *InputComponent->GetName());

		//Bind the input axis
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


void UGrabber::Grab()
{
	GetFirstPhysicsBodyInReach();
	auto HitResult = GetFirstPhysicsBodyInReach();
	auto ComponentToGrab = HitResult.GetComponent();
	AActor* ActorHit = HitResult.GetActor();



	if (ActorHit != nullptr)
	{
		UE_LOG(LogTemp, Warning, TEXT("Looking at: %s"), *(ActorHit->GetName()));
		//PhysicsHandle->GrabComponent(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), true);
		PhysicsHandle->GrabComponentAtLocationWithRotation(ComponentToGrab, NAME_None, ComponentToGrab->GetOwner()->GetActorLocation(), ComponentToGrab->GetOwner()->GetActorRotation());
		UE_LOG(LogTemp, Warning, TEXT("Grabbed!"));
	}

	
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Warning, TEXT("Released!"));
	PhysicsHandle->ReleaseComponent();
}

const FHitResult UGrabber::GetFirstPhysicsBodyInReach()
{
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(OUT viewPointLocation, OUT viewPointRotation);

	FVector LineTraceEnd = viewPointLocation + (viewPointRotation.Vector() * Reach);

	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());

	FHitResult HitResult;
	GetWorld()->LineTraceSingleByObjectType(
		OUT HitResult,
		viewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
	);

	return HitResult;
}

