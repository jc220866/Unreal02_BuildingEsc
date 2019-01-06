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

	/// Look for the PhysicsHandle component attached to our DefaultPawn_BP blueprint.
	/// This pointer is of type UPhysicsHandleComponent, it stores the PhysicsHandle component attached to our DefaultPawn_BP.
	/// From Grabber, we go back up to owner via GetOwner(), then we come back down to find the attached PhysicsHandle component.
	/// These angle brackets are something called a 'generic signature'.
	/// FindComponentbyClass will work for multiple different classes. Here, the class is UPhysicsHandleComponent.
	PhysicsHandlePointer = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();

	if (PhysicsHandlePointer) // If our PhysicsHandlePointer is not 'nullptr'
	{
		// The PhysicsHandle component has been found. Do nothing.
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PhysicsHandle component not found on %s."), *GetOwner()->GetName());
	}

	/// Look for attached InputComponent (only appears at run time!)
	InputComponentPointer = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponentPointer)
	{
		UE_LOG(LogTemp, Warning, TEXT("InputComponent found for %s."), *GetOwner()->GetName());

		// Bind the Grabber input action. 
		/// FName ActionName ("Grab") must be spelled exactly the same as in the Unreal input panel.
		/// IE_Pressed is when button is pressed. There is also IE_Released.
		/// "this" is the 'object' this is operating on, it is a reference to Grabber itself.
		/// notice how the reference to (the address of) UGrabber::Grab() has omitted the parentheses.
		/// To summarize: Action Name, when button is Pressed, reference Grabber, look for the Grab function.
		InputComponentPointer->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("InputComponent not found for %s. You may be unable to move."), *GetOwner()->GetName());
	}

	// ...
	
}

void UGrabber::Grab()
{
	// do something

	UE_LOG(LogTemp, Warning, TEXT("Grab pressed!"));
}

// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/// get player viewpoint this tick. These variables were defined in the header file.
	/// GetPlayerViewPoint takes in two variables and changes them! Naughty getter.
	/// To signify that this naughty getter is changing variables, we defined a blank keyword 'OUT' for our benefit.
	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation, 
		OUT PlayerViewPointRotation
	);

	/// Remember to put a comma after the TEXT(""). Highlight text, hold Ctrl, then hold K, then press C.
	/*
	UE_LOG(LogTemp, Log, TEXT("%s, %s"), 
		*PlayerViewPointLocation.ToString(), 
		*PlayerViewPointRotation.ToString()
	); */

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

	bool bLineTraceHit;
	FHitResult LineTraceHitResult;

	/// bInTraceComplex is asking whether the collision detection be 'simple' or 'complex' collision, player vs visibility.
	/// *InIgnoreActor is asking which actor to ignore. We say our player since we don't want the grabber picking our own pawn up.
	FCollisionQueryParams LineTraceParameters(FName(TEXT("")), false, GetOwner());

	// ray-cast / line-trace out to a maximum of 'reach-distance'
	/// LineTraceMulti passes through multiple objects and provides multiple answers in an array.
	/// ByObjectType is referring to the 'type' of the object, such as 'PhysicsBody' in the case of our chairs and tables.
	bLineTraceHit = GetWorld()->LineTraceSingleByObjectType(
		OUT LineTraceHitResult,					// Updates our blank FHitResult with information of what we've hit with our trace.
		PlayerViewPointLocation,
		LineTraceEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody), // Specific object types we're looking for
		LineTraceParameters												// Additional parameters defined above
	);

	if (bLineTraceHit) /// Logging out the name of the actor our LineTrace hits
	{
		UE_LOG(LogTemp, Log, TEXT("This is a %s"), *LineTraceHitResult.GetActor()->GetName())
	}

	// ...
}
