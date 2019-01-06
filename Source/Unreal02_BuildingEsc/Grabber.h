// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

// So we can create a pointer of type UPhysicsHandleComponent
#include "PhysicsEngine/PhysicsHandleComponent.h"

// So we can create a pointer of type UInputComponent
#include "Components/InputComponent.h"

// Generated.h files should be at the bottom of the includes of a header file
#include "Grabber.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class UNREAL02_BUILDINGESC_API UGrabber : public UActorComponent
{
	GENERATED_BODY()

public:	

	// Sets default values for this component's properties
	UGrabber();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

// Protected is Private but it is accessible to every class that inherits from this class!
protected:

	// Called when the game starts
	virtual void BeginPlay() override;

private:

	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	// This float defines how far, in centimeters, the distance which the player can grab objects from.
	UPROPERTY(EditAnywhere)
		float Reach = 200.f;

	/*
	 This is a pointer to the PhysicsHandle component attached to our DefaultPawn_BP blueprint.
	 We don't necessarily know that the PhysicsHandle component attached to our DefaultPawn has 'spun up' before Grabber
	 So we need to wait until the game starts at BeginPlay to go and find this PhysicsHandle, so we initialize the pointer to null.
	*/
	UPhysicsHandleComponent* PhysicsHandlePointer = nullptr;
	UInputComponent* InputComponentPointer = nullptr;

	// Find (assumed) attached physics handle component
	void LookForAttachedPhysicsHandleComponent();

	// Setup (assumed) attached input component
	void SetupInputComponent();

	// Ray-case / Line-trace and grab what's within reach.
	void Grab();
	void Release();

	// Return hit for first physics body within reach
	FHitResult GetFirstPhysicsBodyInReach() const;
};
