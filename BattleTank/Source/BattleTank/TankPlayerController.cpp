// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	//UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play !"));

	ATank *ControlledTank = nullptr;

	ControlledTank = GetControlledTank();

	if (ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT ("TankPlayercontroller -> tank name: %s"), *ControlledTank->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("No tank is possessed by the TankPlayerController"));
	}
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FString Time;

	AimTowardsCrosshair();

	//Time = FTimespan::FromSeconds(UGameplayStatics::GetRealTimeSeconds(GetWorld())).ToString();

	//UE_LOG(LogTemp, Warning, TEXT("Elapsed time is: %s"), *Time);

}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
	
	FVector HitLocation; // OutParameter

	GetSightRayHitLocation(HitLocation);

	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect". is going to line trace 
	{
		    //UE_LOG(LogTemp, Warning, TEXT("Look direction is: %s"), *HitLocation.ToString())
			// TODO Tell controlled tank to aim at this point
	}

	// Get world location if linetrace through crosshair
	// If it hits landscape
	   // Tell controlled tank to aim at this point
}

// Get World location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	int32 ViewPortSizeX, ViewPortSizeY;
	FVector LookDirection;

	// Get the position of the crosshair in pixels
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	FVector2D ScreenLocation(ViewPortSizeX*CrossHairXLocation, ViewPortSizeY*CrossHairYLocation);

	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		// Line-Trace from the current pawn through the position of the crosshair and identify if we hit anything
		UE_LOG(LogTemp, Warning, TEXT("The de-projected direction is: %s"), *LookDirection.ToString());
	}

	HitLocation = FVector(1.0);
	return true;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector CameraWorldLocation; // temporary variable - to be discarded

	return DeprojectScreenPositionToWorld(ScreenLocation.X, 
		                                  ScreenLocation.Y,
		                                  CameraWorldLocation, 
		                                  LookDirection);
}


//
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


