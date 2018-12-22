// Fill out your copyright notice in the Description page of Project Settings.

#include "Grabber.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

// So we can draw debug lines.
#include "DrawDebugHelpers.h"

// To signify when an argument is 'output', when it is receiving a value from a function.
#define OUT

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

	UE_LOG(LogTemp, Warning, TEXT("Grabber reporting for duty!"));

	// ...
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// get player viewpoint this tick. These variables were defined in the header file.
	// GetPlayerViewPoint takes in two variables and changes them! Naughty getter.
	// To signify that this naughty getter is changing variables, we defined a blank keyword 'OUT' for our benefit.
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);

	// Remember to put a comma after the TEXT(""). Highlight text, hold Ctrl, then hold K, then press C.
	UE_LOG(LogTemp, Log, TEXT("%s, %s"), 
		*PlayerViewPointLocation.ToString(), 
		*PlayerViewPointRotation.ToString()
	);

	// Calculating the end of our line trace every frame
	FVector LineTraceEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Reach;

	// Draw a red debug-line in the world to visualize our grabber
	DrawDebugLine(
		GetWorld(),
		PlayerViewPointLocation,	// Start point. 
		LineTraceEnd,				// End point
		FColor(255, 0, 255),		// Colour. Takes R, G, B (and optional Alpha?)
		true,						// Persistent lines. Will there be an afterimage?
		0.2f,						// If there are persistent lines, how long do they last?
		0,							// DepthPriority
		0.5f						// The THICCness of the debug line
	);						

	// ray-cast / line-trace out to a maximum of 'reach-distance'

	// ...
}

