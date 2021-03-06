// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankTracks.generated.h"

/**
 *  Is used to set the maximum driving force, and apply forces to the tank
 */
UCLASS(meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTracks : public UStaticMeshComponent
{
	GENERATED_BODY()

private:
	
	TArray< class ASprungWheel *> GetWheels() const;

	virtual void BeginPlay() override;

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

public:

	UTankTracks();

	virtual void OnRegister() override;
	
	// Sets a throttle between -1 and + 1
	UFUNCTION(BlueprintCallable, Category=Input)
	void SetThrottle(float Throttle);

	void DriveTrack(float Throttle);
	
	//Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float TrackMaxDrivingForce = 400000.0; // Assume 40t tank and 1g acceleration
};
