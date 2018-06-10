// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"

void UTankTracks::SetThrottle(float Throttle)
{
	
	//TODO - clamp the throttle values so that the player cannot overdrive
	auto ForceApplied = GetForwardVector()*Throttle*TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}


