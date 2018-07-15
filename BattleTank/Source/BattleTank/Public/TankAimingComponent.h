// Copyright EnderIT Ltd.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/GameplayStatics.h"
#include "Components/ActorComponent.h"
#include "Components/SceneComponent.h"
#include "TankAimingComponent.generated.h"

//Enums for the Aiming Component state
UENUM(BlueprintType)
enum class EFiringState : uint8
{
	Reloading,
	Aiming,
	Locked,
	OutOfAmmo,
};

// Forward declaration
class UTankBarrel;
class UTankTurret;
class AProjectile;

//Hold Barrel's properties and Elevate method
UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class BATTLETANK_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

private:
	
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction);
	bool IsRotating = false;

protected:
	
	UTankBarrel *Barrel=nullptr;
	UTankTurret *Turret = nullptr;
	void MoveBarrelTowards(FVector AimDirection);
	void MoveTurretTowards(FVector AimDirection);

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBluePrint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.0;
	
	UPROPERTY(BlueprintReadOnly, Category = "State")
	int Rounds = 3;

	float LastFireTime = 0;

public:	

	// Sets default values for this component's properties
	UTankAimingComponent();
	
	UPROPERTY(BlueprintReadOnly, Category = "State")
	EFiringState FiringState = EFiringState::Reloading;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
	float LaunchSpeed = 4000.0;

	UFUNCTION(BlueprintCallable, Category = "Setup")
	void Initialise(UTankBarrel * BarrelToSet, UTankTurret * TurretToSet);

	void Aim(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Firing")
	void Fire();

	UTankBarrel *GetBarrelReference();
	UTankTurret *GetTurretReference();
	
	UFUNCTION(BlueprintCallable, Category = "Firing")
	int GetRoundsLeft() const;
};
