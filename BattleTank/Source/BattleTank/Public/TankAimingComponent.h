// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "TankAimingComponent.generated.h"

// Forward declaration
class UTankBarrel;

//Hold Barrel's properties and Elevate method

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

protected:

	void MoveBarrelTowards(FVector AimDirection);
	UTankBarrel *Barrel=nullptr;

public:	
	void Aim(FVector HitLocation, float LaunchSpeed);
	void SetBarrelReference(UTankBarrel  * BarrelToSet);
};
