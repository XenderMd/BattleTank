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

		if (ensure(PlayerTank && ControlledTank))
		{
			if (! (GetPawn()->GetName().Find("AutoMortar") >= 0) )
			{
				MoveToActor(PlayerTank, AcceptanceRadius);
			}

			ControlledTank->FindComponentByClass<UTankAimingComponent>()->Aim(PlayerTank->GetActorLocation());

			ControlledTank->FindComponentByClass<UTankAimingComponent>()->Fire();
		}
		else { return; }
	}



