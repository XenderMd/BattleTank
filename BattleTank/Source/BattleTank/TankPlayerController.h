// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Tank.h"
#include "Kismet/GameplayStatics.h"
#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h" // Must be the last include

/**
 * 
 */
UCLASS()
class BATTLETANK_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()


private:

	UPROPERTY (EditAnywhere)
	float CrossHairXLocation = 0.5;

	UPROPERTY(EditAnywhere)
	float CrossHairYLocation = 0.33333;
	
public:

	ATank *GetControlledTank() const;

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;

private:

	// Moves the barel of the tank towards the crosshair
	void AimTowardsCrosshair();
	bool GetSightRayHitLocation(FVector & OutHitLocation) const;
	bool GetLookDirection(FVector2D ScreenLocation, FVector &WorldDirection) const;
	
};
