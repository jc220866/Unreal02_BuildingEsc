// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"

// So we can access the Actor class and use GetOwner().
#include "GameFramework/Actor.h"

// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame. 
	// You can turn these features off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}

// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	// GetOwner returns a pointer to an object of type AActor, GetName returns a string containing the name of that AActor.
	FString ObjectName = GetOwner()->GetName();

	// GetTransform returns an FTransform. From that, GetLocation returns a vector, it has a function called ToString which, of course, converts it to a string.
	FString ObjectPosition = GetOwner()->GetTransform().GetLocation().ToString();

	// CompactString appears to only return the difference from 0, with one less decimal point too.
	FString ObjectPositionCompact = GetOwner()->GetTransform().GetLocation().ToCompactString();

	// Purple things are macros? LogTemp is a log category. Warning is Yellow colour.
	// The star here is NOT a pointer, though it is SIMILAR to de-referencing. It's an overloaded operator.
	UE_LOG( LogTemp, Warning, TEXT( "Ayo boi its %s, how you doin? I repeat, this is %s." \
		" I'm at %s. Again, that's %s." ), *ObjectName, *GetOwner()->GetName(), *ObjectPosition, *ObjectPositionCompact );


	// GetACTORLocation returns the RootComponent's location.
	FString ObjectPosRoot = GetOwner()->GetActorLocation().ToString();

	// GetTransform vs GetActorTransform is that the latter will return the transform of the RootComponent of the actor.
	FString ObjectPosRootAlt = GetOwner()->GetActorTransform().GetLocation().ToString();
}

// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}
