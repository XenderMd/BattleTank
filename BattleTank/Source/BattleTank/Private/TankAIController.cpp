// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Tank.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	ATank *ControlledTank = Cast<ATank>(GetPawn());
	ATank *PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

		if (PlayerTank)
		{
			MoveToActor(PlayerTank, AcceptanceRadius); // TODO Check the radius is in cm

			ControlledTank->AimAt(PlayerTank->GetActorLocation());

			ControlledTank->Fire();
		}
	}



