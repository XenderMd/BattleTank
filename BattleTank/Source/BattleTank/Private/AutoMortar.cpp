// Copyright EnderIT Ltd.

#include "AutoMortar.h"


// Sets default values
AAutoMortar::AAutoMortar()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AAutoMortar::BeginPlay()
{
	Super::BeginPlay();
	CurrentHealth = StartingHealth;
}

// Called every frame
void AAutoMortar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AAutoMortar::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

float AAutoMortar::TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	DamagePoints = FMath::Clamp(DamagePoints, 0, CurrentHealth);
	CurrentHealth = CurrentHealth - DamagePoints;
	
	if (CurrentHealth <= 0) { OnDeath.Broadcast(); }

	return DamageAmount;
}

float AAutoMortar::GetHealthPercent()
{
	return (float)CurrentHealth / float(StartingHealth);
}

