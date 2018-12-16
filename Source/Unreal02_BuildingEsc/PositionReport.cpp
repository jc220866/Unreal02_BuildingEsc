// Fill out your copyright notice in the Description page of Project Settings.

#include "PositionReport.h"

// So we can access the Actor class and use GetOwner().
#include "GameFramework/Actor.h"


// Sets default values for this component's properties
UPositionReport::UPositionReport()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPositionReport::BeginPlay()
{
	Super::BeginPlay();

	// GetOwner returns a pointer to an object of type AActor, GetName returns a string containing the name of that AActor.
	FString ObjectName = GetOwner()->GetName();

	// Purple things are macros? LogTemp is a log category. Warning is Yellow colour.
	// The star here is NOT a pointer, though it is SIMILAR to de-referencing. It's an overloaded operator.
	UE_LOG( LogTemp, Warning, TEXT( "Ayo boi its %s, how you doin? I repeat, this is %s." ), *ObjectName, *GetOwner()->GetName() );

	// ...
}


// Called every frame
void UPositionReport::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

