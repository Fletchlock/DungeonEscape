// Copyright GreyHone Games

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/TriggerVolume.h"
// Add new #include above this line
#include "OpenDoor.generated.h"


UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class DUNGEONESCAPE_API UOpenDoor : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOpenDoor();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	void FindAudioComponent();
	void CheckForPressurePlate() const;
	void OpenDoor(float DeltaTime);
	void CloseDoor(float DletaTime);
	float TotalMassOfActors() const;

	bool doorSoundPlaying = false;
	

private:

	float InitialYaw;
	float CurrentYaw;

	UPROPERTY()
	UAudioComponent* AudioComponent = nullptr;
	
	UPROPERTY(EditAnywhere, Category = "Door Properties", meta = (ClampMin = "-90.0", ClampMax = "90.0"))
	float DoorOpenAngle = -90.0f;

	UPROPERTY(EditAnywhere, Category = "Door Properties", meta = (ClampMin = "0.1", ClampMax = "10.0"))
	float DoorOpenSpeed = 2.f;

	UPROPERTY(EditAnywhere, Category = "Door Properties", meta = (ClampMin = "0.1", ClampMax = "10.0"))
	float DoorCloseSpeed = 2.f;

	UPROPERTY(EditAnywhere, Category = "Door Properties", meta = (ClampMin = "0.1", ClampMax = "10.0"))
	float DoorCloseDelay = 2.f;
	
	UPROPERTY(EditAnywhere, Category = "Pressure Plate")
	ATriggerVolume* PressurePlate = nullptr;

	UPROPERTY(EditAnywhere, Category = "Pressure Plate")
	float MassToOpenDoor = 50.f;

	float DoorLastOpened = 0.f;
};
