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

	// Check for Physics Handle Component
	PhysicsHandle = GetOwner()->FindComponentByClass<UPhysicsHandleComponent>();
	if (!PhysicsHandle)
	{
		UE_LOG(LogTemp, Error, TEXT("No Physics Handle Component found on %s"), *GetOwner()->GetName());
	}

	InputComponent = GetOwner()->FindComponentByClass<UInputComponent>();
	if (InputComponent)
	{
		InputComponent->BindAction("Grab", IE_Pressed, this, &UGrabber::Grab);
		InputComponent->BindAction("Grab", IE_Released, this, &UGrabber::Release);
	}
}

void UGrabber::Grab()
{
	UE_LOG(LogTemp, Display, TEXT("Grabber pressed!"));
}

void UGrabber::Release()
{
	UE_LOG(LogTemp, Display, TEXT("Grabber released!"));
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
	
	//Set variables for line trace and DrawDebugLine()
	FColor TraceColor = { 255, 0, 0 };
	FVector LineStart = PlayerViewPointLocation;
	FVector LineEnd = PlayerViewPointLocation + PlayerViewPointRotation.Vector() * Range;

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

	FCollisionQueryParams TraceParams(FName(TEXT("")), false, GetOwner());
	FHitResult Hit;
	// Ray-cast (line trace) out to certain distance (Reach)
	GetWorld()->LineTraceSingleByObjectType(
		OUT Hit,
		LineStart,
		LineEnd,
		FCollisionObjectQueryParams(ECollisionChannel::ECC_PhysicsBody),
		TraceParams
		);

	// See what we are hitting
	AActor* HitResult =  Hit.GetActor();

	if (HitResult)
	{
	UE_LOG(LogTemp, Warning, TEXT("Hit : %s"), *(HitResult->GetName()));
	}

	// Logging out to test
}

