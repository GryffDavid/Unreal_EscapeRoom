// (C) Copyright Gryffydd David 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "Components/PrimitiveComponent.h"
#include "OpenDoor.generated.h"
 
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnOpenRequest);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnCloseRequest);

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

	public:	
		// Sets default values for this component's properties
		UOpenDoor();
		UPROPERTY(BlueprintAssignable)
			FOnOpenRequest OnOpenRequest;

		UPROPERTY(BlueprintAssignable)
			FOnOpenRequest OnCloseRequest;

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;

	public:	
		// Called every frame
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;		

	private:
		AActor* Owner;
		float GetTotalMassOfActorsOnPlate();
	
		UPROPERTY(EditAnywhere)
			ATriggerVolume* PressurePlate;
		
		UPROPERTY(EditAnywhere)
			float TriggerMass = 50.0f;
};
