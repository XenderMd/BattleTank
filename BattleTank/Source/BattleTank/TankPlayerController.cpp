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
		UE_LOG(LogTemp, Warning, TEXT("HitLocation is: %s"), *HitLocation.ToString())
			// TODO Tell controlled tank to aim at this point
	}

	// Get world location if linetrace through crosshair
	// If it hits landscape
	   // Tell controlled tank to aim at this point
}

// Get World location of linetrace through crosshair, true if hits landscape
bool ATankPlayerController::GetSightRayHitLocation(FVector & HitLocation) const
{
	// Get current pawn position
	// Get the position in pixels of the crosshair
	// Gaycast from the current pawn through the position of the crosshair
	// Identify if we hit anything

	HitLocation = FVector(1.0);
	return false;
}


//
ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


