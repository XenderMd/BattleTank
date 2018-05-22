// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


// Called when the game starts
void UTankAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UTankAimingComponent::Aim(FVector HitLocation, float LaunchSpeed)
{
	if (!Barrel) {return;}

	auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	FVector OutLaunchVelocity(0);

	GetOwner();

	if (UGameplayStatics::SuggestProjectileVelocity(
		GetWorld(), 
		OutLaunchVelocity, 
		StartLocation, 
		HitLocation, 
		LaunchSpeed, 
		false,
		0.0,
		0.0,
		ESuggestProjVelocityTraceOption::DoNotTrace))
	{
		auto OutDirection = OutLaunchVelocity.GetSafeNormal();
		auto TankName = GetOwner()->GetName();
		UE_LOG(LogTemp, Warning, TEXT("%s is firing in the direction %s "), *TankName, *OutDirection.ToString());
	}
}

void UTankAimingComponent::SetBarrelReference(UStaticMeshComponent * BarrelToSet)
{
	Barrel = BarrelToSet;
}

