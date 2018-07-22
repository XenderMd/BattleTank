//Copyright EnderIT Ltd.

#include "TankAimingComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankBarrel.h"
#include "TankTurret.h"
#include "Projectile.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}

void UTankAimingComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction)
{
	if (Rounds <= 0)
	{
		FiringState = EFiringState::OutOfAmmo;
	}
	else if (!((FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds))
	{
		FiringState = EFiringState::Reloading;
	}
	else if (IsRotating)
	{
		FiringState = EFiringState::Aiming;
	}
	else
	{
		FiringState = EFiringState::Locked;
	}
}


void UTankAimingComponent::Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet)
{
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::Aim(FVector HitLocation)
{
	if (!Barrel || !Turret) {return;}

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
		MoveTurretTowards(AimDirection);
	}
	else
	{
		MoveBarrelTowards(FVector(0));
		//No aim solution found
	}
}

UTankBarrel * UTankAimingComponent::GetBarrelReference()
{
	return Barrel;
}

UTankTurret * UTankAimingComponent::GetTurretReference()
{
	return Turret;
}

int32 UTankAimingComponent::GetRoundsLeft() const
{
	return Rounds;
}

void UTankAimingComponent::MoveBarrelTowards(FVector AimDirection)
{
	
	// translate the AimDirection from FVector to FRotator
	auto BarelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();

	// Work-out the difference between the current and the future position
	auto DeltaRotator = AimAsRotator - BarelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector AimDirection)
{
	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = AimDirection.Rotation();
	
	if (Barrel->GetForwardVector().Equals(AimDirection, 0.05))
	{
		IsRotating = false;
	}
	else
	{
		IsRotating = true;
	}

	// Work-out the difference between the current and the future position
	auto DeltaRotator = AimAsRotator - TurretRotator;

	if (FMath::Abs(DeltaRotator.Yaw) < 180)
	{
		Turret->Rotate(DeltaRotator.Yaw);
	}
	else
	{
		Turret->Rotate(-DeltaRotator.Yaw);
	}
}

void UTankAimingComponent::Fire()
{
	if (FiringState != EFiringState::OutOfAmmo && FiringState != EFiringState::Reloading)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint,
			GetBarrelReference()->GetSocketLocation(FName("Projectile")),
			GetBarrelReference()->GetSocketRotation(FName("Projectile")));
		if (ensure(Projectile))
		{
			Projectile->LaunchProjectile(LaunchSpeed);
			Rounds--;
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("Invalid Projectile reference"));
		}
		LastFireTime = FPlatformTime::Seconds();
	}
}