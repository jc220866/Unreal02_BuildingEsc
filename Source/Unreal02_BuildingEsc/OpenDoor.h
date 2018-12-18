// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
#include "OpenDoor.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL02_BUILDINGESC_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UOpenDoor();

// Protected is Private but it is accessible to every class that inherits from this class!
protected: 
	// Called when the game starts
	virtual void BeginPlay() override;

	void OpenDoor();
	void CloseDoor();

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

private:

	// Setting the UPROPERTY of this variable to EditAnywhere allows us to edit it in the component menu in the Details tab.
	UPROPERTY(EditAnywhere)
		float OpenAngle = 135.0f;

	// This variable is a pointer to any object of type 'ATriggerVolume', like the trigger volume boxes in Unreal.
	UPROPERTY(EditAnywhere)
		ATriggerVolume* PressurePlate;
	
	// This variable is a pointer to any object of type 'AActor', which could be a player character/pawn or a chair.
	AActor* ActorThatOpens; // Pawn inherits from actor

	UPROPERTY(EditAnywhere)
		float DoorCloseDelay = 1.0f;

	float LastDoorOpenTime;

	AActor* Owner;

	float StartingRoll;
	float StartingPitch;
	float StartingYaw;

	float CurrentYaw; // = GetOwner()->GetActorRotation().Yaw;
};
