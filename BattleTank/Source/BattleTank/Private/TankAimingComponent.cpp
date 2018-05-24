// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "TankBarrel.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}



void UTankAimingComponent::Aim(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) {return;}

	auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector OutLaunchVelocity(0);

	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		GetWorld(),
		OutLaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0.0,
		0.0,
		ESuggestProjVelocityTraceOption::DoNotTrace);

	if (bHaveAimSolution)
	{
		auto AimDirection = OutLaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(AimDirection);
	}
}

void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet)
{
	Barrel = BarrelToSet;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	
	
	// translate the AimDirection from FVector to FRotator
	auto BarelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();

	// Work-out the difference between the current and the future position
	auto DeltaRotator = AimAsRotator - BarelRotator;

	//UE_LOG(LogTemp, Warning, TEXT("DeltaRotator is %s"), *DeltaRotator.ToString());

	Barrel->Elevate(5); // TODO Remove magic number
}

