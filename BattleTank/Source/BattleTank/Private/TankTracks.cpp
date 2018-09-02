// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"
#include "SprungWheel.h"
#include"SpawnPoint.h"

UTankTracks:: UTankTracks()
{
	
}

TArray <ASprungWheel*> UTankTracks::GetWheels() const
{
	TArray<ASprungWheel*> ResultArray;
	TArray <USceneComponent *> Children;
	GetChildrenComponents(true, Children);
	for (USceneComponent*Child : Children)
	{
		auto SpawnPointChild = Cast<USpawnPoint>(Child);
		if (!SpawnPointChild) continue;
		AActor *SpawnedChild = SpawnPointChild->GetSpawnedActor();	
		
		auto SprungWheel = Cast<ASprungWheel>(SpawnedChild);
		
		if (!SprungWheel) continue;
		
		ResultArray.Add(SprungWheel);
	}

	return ResultArray;
}

void UTankTracks::BeginPlay()
{
	Super::BeginPlay();
}


// Bug Fix - since we removed previously the TickComponent, we had to explicitly Register this component again, to enable the Ticking (Lessons Q&A)
void  UTankTracks::OnRegister()
{
	Super::OnRegister();
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTracks::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


void UTankTracks::SetThrottle(float Throttle)
{
	float CurrentThrottle = FMath::Clamp<float>(Throttle, -2.0, 2.0);
	DriveTrack(CurrentThrottle);
}

void UTankTracks::DriveTrack(float Throttle)
{
	auto ForceApplied = Throttle*TrackMaxDrivingForce;

	
	auto Wheels = GetWheels();

	if (Wheels.Num() != 0)
	{
		auto ForcePerWheel = ForceApplied / Wheels.Num();
		
		for (ASprungWheel *Wheel : Wheels)
		{
			Wheel->AddDrivingForce(ForcePerWheel);
		}
	}
}


