// Fill out your copyright notice in the Description page of Project Settings.

#include "OpenDoor.h"

// So we can access the Actor class and use GetOwner().
#include "GameFramework/Actor.h"

// So we can access the GetWorld() function.
#include "Engine/World.h"

// To signify when an argument is 'output', when it is receiving a value from a function.
#define OUT


// Sets default values for this component's properties
UOpenDoor::UOpenDoor()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
}

// Called when the game starts
void UOpenDoor::BeginPlay()
{
	Super::BeginPlay();

	Owner = GetOwner();

	StartingRoll = GetOwner()->GetActorRotation().Roll;
	StartingPitch = GetOwner()->GetActorRotation().Pitch;
	StartingYaw = Owner->GetActorRotation().Yaw;

	// Although this variable is of type AActor*, we are fine to send a APawn* because Pawns inherit from Actors. Pawns ARE Actors.
	// This gets the default PlayerController in our world, then the pawn it is controlling.
	// ActorThatOpens = GetWorld()->GetFirstPlayerController()->GetPawn();
}

void UOpenDoor::OpenDoor()
{
	FRotator OpenRotation = FRotator(StartingPitch, OpenAngle, StartingRoll);

	Owner->SetActorRotation(OpenRotation);
}

void UOpenDoor::CloseDoor()
{
	FRotator CloseRotation = FRotator(StartingPitch, StartingYaw, StartingRoll);

	Owner->SetActorRotation(CloseRotation);
}

float UOpenDoor::GetTotalMassOfActorsOnPressurePlate()
{
	// Give me a list of AActor*s (pointers to actors).
	TArray<AActor*> ActorsOnPressurePlate;
	PressurePlate->GetOverlappingActors(OUT ActorsOnPressurePlate);

	// Iterate through the Actors on the Pressure Plate and sum their masses.
	float MassOfActorsOnPressurePlate = 0.0f;

	/// const emphasizes that the Actor does not change in this process
	for (const AActor *ActorPointer : ActorsOnPressurePlate)
	{
		UE_LOG(LogTemp, Warning, TEXT("Actor on pressure plate: %s"), *ActorPointer->GetName());

		MassOfActorsOnPressurePlate += ActorPointer->FindComponentByClass<UPrimitiveComponent>()->GetMass();
	}
	return MassOfActorsOnPressurePlate;
}

//// TODO FOR OPENING A DOOR, WE SHOULD USE DeltaSeconds INSTEAD OF TICKRATE ////

// Called every frame
void UOpenDoor::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// poll the trigger volume every frame
	if (GetTotalMassOfActorsOnPressurePlate() >= TriggerMass)
	{
		OpenDoor();
		
		// Store the time at which the door last opened, in order to accurately add a delay.
		LastDoorOpenTime = GetWorld()->GetTimeSeconds();
	}

	// if enough time has passed for the door to close
	if (GetWorld()->GetTimeSeconds() > (LastDoorOpenTime + DoorCloseDelay))
	{
		CloseDoor();
	}

	/*		this code successfully makes the door twirl around continuously.

	// FRotator stores a tuple of three floats representing the X, Y and Z rotation. GetActorRotation gets the RootComponent rotation.
	FRotator CurrentRotation = GetOwner()->GetActorRotation();

	// Here we get the current X, Y and Z axis rotations respectively. 
	float StartingRoll = GetOwner()->GetActorRotation().Roll;
	float StartingPitch = GetOwner()->GetActorRotation().Pitch;
	float CurrentYaw = GetOwner()->GetActorRotation().Yaw;

	float YawIncrement = 1.0f;
	float NewYaw = (CurrentYaw + YawIncrement);

	// FRotator constructor wants Y(Pitch), Z(Yaw) and X(Roll) axis. What a frustratingly arbitrary order.
	FRotator NewRotation = FRotator(StartingPitch, NewYaw, StartingRoll);

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
