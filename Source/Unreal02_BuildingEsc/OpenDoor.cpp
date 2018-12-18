// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

// So we can access the Actor class and use GetOwner().
#include "GameFramework/Actor.h"

#include "Engine/World.h"

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

	// Although this variable is of type AActor*, we are fine to send a APawn* because Pawns inherit from Actors. Pawns ARE Actors.
	ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();

	// ...
	
}

void UOpenDoor::OpenDoor()
{
	float CurrentRoll = GetOwner()->GetActorRotation().Roll;
	float CurrentPitch = GetOwner()->GetActorRotation().Pitch;
	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;

	FRotator NewRotation = FRotator(CurrentPitch, OpenAngle, CurrentRoll);

	GetOwner()->SetActorRotation(NewRotation);
}

//// TODO FOR OPENING A DOOR, WE SHOULD USE DeltaSeconds INSTEAD OF TICKRATE ////

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// poll the trigger volume every frame
	// if the actor that opens is in the volume
	if (PressurePlate->IsOverlappingActor(ActorThatOpens))
	{
		OpenDoor();
	}

	/*		this code successfully makes the door twirl around continuously.

	// FRotator stores a tuple of three floats representing the X, Y and Z rotation. GetActorRotation gets the RootComponent rotation.
	FRotator CurrentRotation = GetOwner()->GetActorRotation();

	// Here we get the current X, Y and Z axis rotations respectively. 
	float CurrentRoll = GetOwner()->GetActorRotation().Roll;
	float CurrentPitch = GetOwner()->GetActorRotation().Pitch;
	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;

	float YawIncrement = 1.0f;
	float NewYaw = (CurrentYaw + YawIncrement);

	// FRotator constructor wants Y(Pitch), Z(Yaw) and X(Roll) axis. What a frustratingly arbitrary order.
	FRotator NewRotation = FRotator(CurrentPitch, NewYaw, CurrentRoll);

	GetOwner()->SetActorRotation(NewRotation);

	*/

	// ...

	/*			medium fail. When making a new FRotator, you gotta put FRotator infront of the brackets...

	FRotator NewRotation = (0, 0, NewYaw);

	GetOwner()->SetActorRotation((0.0f, 0.0f, NewYaw));

	*/

	/*				big fail. We don't want to fiddle with quaternions

	// create a variable with the current rotation of the object
	// FQuat CurrentRotation = GetOwner()->GetTransform().GetRotation();
	FVector X = GetOwner()->GetTransform().GetRotation().GetAxisX();
	FVector Y = GetOwner()->GetTransform().GetRotation().GetAxisY();
	FVector CurrentRotationZ = GetOwner()->GetTransform().GetRotation().GetAxisZ();

	float AmountToRotateBy = 6.0f;

	// every frame, set the rotation of the object to be its current rotation + 6.0
	FVector NewRotationZ = (CurrentRotationZ + AmountToRotateBy);
	FQuat NewRotationFull = (X, Y, NewRotationZ);

	// apply the new Z axis to the object's rotation
	GetOwner()->GetTransform().SetRotation(NewRotationFull);

	*/
}

