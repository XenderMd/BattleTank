// Copyright EnderIT Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Tank.generated.h"

class UTankBarrel; // Forward declaration
class UTankTurret;
class UTankAimingComponent;
class AProjectile;
class UTankMovementComponent;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()


private:
	// Sets default values for this pawn's properties
	ATank();

	UPROPERTY(EditDefaultsOnly, Category = Setup)
	TSubclassOf<AProjectile> ProjectileBluePrint;

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float LaunchSpeed = 4000.0; // TODO - a research on the actuall speed of the tank shell

	UPROPERTY(EditDefaultsOnly, Category = Firing)
	float ReloadTimeInSeconds = 3.0;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	float LastFireTime = 0;

protected:

	//Component not required however - it spawned directly in UE and works independently (in parallel) from the Tank class code.  
	UPROPERTY(BlueprintReadOnly)
	UTankMovementComponent *TankMovementComponent = nullptr;

public:	

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly)
	UTankAimingComponent * TankAimingComponent = nullptr;

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

	// Function created only to maintain consistency - since we have a TankMovementComponent pointer. It is set to the Movement Component from the Tank_BP.
	// Not required however as well - can be removed together with the pointer
	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetMovementComponentReference(UTankMovementComponent *MovementComponentReference);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetAimingComponentReference(UTankAimingComponent *AimingComponentReference);

	void AimAt(FVector HitLocation);
};
