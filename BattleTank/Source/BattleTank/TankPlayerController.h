// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "Runtime/Engine/Classes/Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include


class ATank;
/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


private:

	UPROPERTY (EditDefaultsOnly)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditDefaultsOnly)
	float CrossHairYLocation = 0.33333;

	UPROPERTY(EditDefaultsOnly)
	float LineTraceRange = 1000000;

protected:
	
	UFUNCTION (BlueprintCallable, Category = "Setup")
	ATank *GetControlledTank() const;

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	// Moves the barel of the tank towards the crosshair
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector & OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector &WorldDirection) const;
	bool GetLookVectorHitLocation(FVector LookDirection, FVector &OutHitLocation) const;
	
};
