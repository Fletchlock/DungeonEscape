// Copyright GreyHone Games

#include "Grabber.h"
#include "DrawDebugHelpers.h"
#include "GameFramework/PlayerController.h"
#include "Engine/World.h"

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
	
}


// Called every frame
void UGrabber::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Get players viewpoint
	FVector PlayerViewPointLocation;
	FRotator PlayerViewPointRotation;

	GetWorld()->GetFirstPlayerController()->GetPlayerViewPoint(
		OUT PlayerViewPointLocation,
		OUT PlayerViewPointRotation
	);

	// Logging out to test
	//FString Location = PlayerViewPointLocation.ToString();
	//FString Rotation = PlayerViewPointRotation.ToString();
	UE_LOG(LogTemp, Warning, TEXT("Players ViewPoint Location : %s Players ViewPoint Rotation : %s"),
		*PlayerViewPointLocation.ToString(),
		*PlayerViewPointRotation.ToString()
	);

	//Set variables for line trace
	
	FColor TraceColor = { 255, 0, 0 };
	FVector LineStart = PlayerViewPointLocation;
	FVector LineEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Range;

	// Ray-cast (line trace) out to certain distance (Reach)
	DrawDebugLine(
		GetWorld(),
		LineStart,
		LineEnd,
		TraceColor,
		false,
		-1.f,
		0,
		2.f
	);


	// See what we are hitting

}

