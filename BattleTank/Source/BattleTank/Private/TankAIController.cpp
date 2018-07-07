// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"

void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

}


void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	auto *ControlledTank = GetPawn();
	auto *PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();

		if (ensure(PlayerTank && PlayerTank))
		{
			MoveToActor(PlayerTank, AcceptanceRadius); // TODO Check the radius is in cm

			ControlledTank->FindComponentByClass<UTankAimingComponent>()->Aim(PlayerTank->GetActorLocation());

			ControlledTank->FindComponentByClass<UTankAimingComponent>()->Fire();
		}
		else { return; }
	}



