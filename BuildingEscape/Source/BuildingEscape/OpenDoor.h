// (C) Copyright Gryffydd David 2019

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "Engine/World.h"
#include "OpenDoor.generated.h"

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BUILDINGESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

	public:	
		// Sets default values for this component's properties
		UOpenDoor();

	protected:
		// Called when the game starts
		virtual void BeginPlay() override;

		void OpenDoor();

	public:	
		// Called every frame
		virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	private:
		AActor* Owner;

		///0 = Wide Open
		UPROPERTY(EditAnywhere)
			float OpenAngle = 0.0f;

		UPROPERTY(EditAnywhere)
			ATriggerVolume* PressurePlate;

		UPROPERTY(EditAnywhere)
			float DoorCloseDelay = 0.5f;

		float LastDoorOpenTime = 0.0f;
		FRotator DoorStartRotation;

		AActor* ActorThatOpens;
};
