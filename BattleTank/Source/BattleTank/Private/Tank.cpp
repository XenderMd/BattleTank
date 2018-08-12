// Copyright EnderIT Ltd.

#include "Tank.h"
#include "TankAimingComponent.h"


// Sets default values
ATank::ATank()
{
	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

//Called by the engine everytime when an ApplyDamage event was fired (in this case, the ApplyRadialDamage is fired from the Projectile)
float ATank::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	DamagePoints = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	CurrentHealth = CurrentHealth - DamagePoints;
	
	if (CurrentHealth <= 0) { OnDeath.Broadcast(); }

	//UE_LOG(LogTemp, Warning, TEXT("The damage received is: %d"), CurrentHealth);
	return DamageAmount;
}

float ATank::GetHealthPercent()
{
	return (float)CurrentHealth/float(StartingHealth);
}
