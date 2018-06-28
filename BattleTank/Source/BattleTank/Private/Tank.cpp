// Copyright EnderIT Ltd.

#include "Tank.h"
#include "TankBarrel.h"
#include "Projectile.h"
#include "TankAimingComponent.h"
#include"TankMovementComponent.h"


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ATank::BeginPlay()
{
	Super::BeginPlay();
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ATank::Fire()
{
	bool isReloaded = (FPlatformTime::Seconds() - LastFireTime) > ReloadTimeInSeconds;

	if (isReloaded)
	{
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBluePrint,
			TankAimingComponent->GetBarrelReference()->GetSocketLocation(FName("Projectile")),
			TankAimingComponent->GetBarrelReference()->GetSocketRotation(FName("Projectile")));
		if (Projectile)
		{Projectile->LaunchProjectile(LaunchSpeed);}
		else
		{ UE_LOG(LogTemp, Warning, TEXT("Invalid Projectile reference"));}
		LastFireTime = FPlatformTime::Seconds();
	}
}

void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->Aim(HitLocation, LaunchSpeed);
}

void ATank::SetMovementComponentReference(UTankMovementComponent * MovementComponentReference)
{
	TankMovementComponent = MovementComponentReference;
}

void ATank::SetAimingComponentReference(UTankAimingComponent * AimingComponentReference)
{
	TankAimingComponent = AimingComponentReference;
}
