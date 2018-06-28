// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "TankAimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetControlledTank()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController cannot find the TankAimingComponent at BeginPlay!"))
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

    // Get world location if linetrace through crosshair
	GetSightRayHitLocation(HitLocation);

	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect". is going to line trace 
	{	 
		GetControlledTank()->AimAt(HitLocation);
	}

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
		if (GetLookVectorHitLocation(LookDirection, HitLocation))
		{
			
			return true;
		}
		
	}
	HitLocation = FVector(0.0);
	return false;
}

bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const
{
	FVector CameraWorldLocation; // temporary variable - to be discarded

	return DeprojectScreenPositionToWorld(ScreenLocation.X, 
		                                  ScreenLocation.Y,
		                                  CameraWorldLocation, 
		                                  LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector & OutHitLocation) const
{
	FHitResult HitResult;
	FVector LineTraceStart = PlayerCameraManager->GetCameraLocation();
	FVector LineTraceEnd = LineTraceStart + LookDirection*LineTraceRange;

	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		LineTraceStart,
		LineTraceEnd,
		ECollisionChannel::ECC_Visibility))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}

	OutHitLocation = FVector(0.0);
	return false;
}

ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


