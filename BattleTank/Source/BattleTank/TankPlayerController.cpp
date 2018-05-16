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

	//TODO AimTowardsCrosshair();
	AimTowardsCrosshair();

	Time = FTimespan::FromSeconds(UGameplayStatics::GetRealTimeSeconds(GetWorld())).ToString();

	UE_LOG(LogTemp, Warning, TEXT("Elapsed time is: %s"), *Time);

}

void ATankPlayerController::AimTowardsCrosshair()
{
	if (!GetControlledTank()) { return; }
}


//
ATank* ATankPlayerController::GetControlledTank() const
{
	// Get world location if linetrace through crosshair
	// If it hits landscape
	   // Tell controlled tank to aim at this point

	return Cast<ATank>(GetPawn());
}


