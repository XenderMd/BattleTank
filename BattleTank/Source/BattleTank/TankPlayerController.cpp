// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "TankAimingComponent.h"
#include "Tank.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
	{
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController cannot find the TankAimingComponent at BeginPlay!"))
	}

}

void ATankPlayerController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankPlayerController::OnTankDeath);
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
	
	FVector HitLocation; // OutParameter


	if (GetSightRayHitLocation(HitLocation)) // Has "side-effect". is going to line trace 
	{	
		if (!ensure(GetPawn())) { return; }
		GetPawn()->FindComponentByClass<UTankAimingComponent>()->Aim(HitLocation);
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
		return GetLookVectorHitLocation(LookDirection, HitLocation);
		
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
		ECollisionChannel::ECC_Camera))
	{
		OutHitLocation = HitResult.Location;
		return true;
	}

	OutHitLocation = FVector(0.0);
	return false;
}

void ATankPlayerController::OnTankDeath()
{
	StartSpectatingOnly();
}
