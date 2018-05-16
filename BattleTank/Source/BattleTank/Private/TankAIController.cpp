// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//UE_LOG(LogTemp, Warning, TEXT("PlayerController Begin Play !"));

	ATank *ControlledTank = nullptr;
	ATank *PlayerControllerTank = nullptr;

	ControlledTank = GetControlledTank();
	PlayerControllerTank = GetPlayerTank();

	if (PlayerControllerTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s -> PlayerControllerTank name is %s"), *GetControlledTank()->GetName(), *PlayerControllerTank->GetName())
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerControllerTank not found"));
	}
}


ATank* ATankAIController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank * ATankAIController::GetPlayerTank() const
{
	return Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}






