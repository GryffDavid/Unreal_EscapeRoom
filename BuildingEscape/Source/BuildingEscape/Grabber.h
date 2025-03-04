// (C) Copyright Gryffydd David 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PhysicsEngine/PhysicsHandleComponent.h"
#include "Components/PrimitiveComponent.h"

#include "Grabber.generated.h"



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

	public:	
		// Sets default values for this component's properties
		UGrabber();

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;

		void FindPhysicsHandleComponent();

		void SetupInputComponent();

	public:	
		// Called every frame
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	private:
		FVector viewPointLocation;
		FRotator viewPointRotation;

		UPROPERTY(EditAnywhere)
		float Reach = 100.f;

		UPhysicsHandleComponent* PhysicsHandle = nullptr;
		UInputComponent* InputComponent = nullptr;
		void Grab();
		void Release();
		const FHitResult GetFirstPhysicsBodyInReach();
		FVector GetReachLineEnd();
};
