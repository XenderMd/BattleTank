// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "TankAimingComponent.h"
#include"Tank.h"

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

void ATankAIController::SetPawn(APawn * InPawn)
{
	Super::SetPawn(InPawn);
	if (InPawn)
	{
		auto PossessedTank = Cast<ATank>(InPawn);
		if (!ensure(PossessedTank)) { return; }
		PossessedTank->OnDeath.AddUniqueDynamic(this, &ATankAIController::OnTankDeath);
	}
}

void ATankAIController::OnTankDeath()
{
	UE_LOG(LogTemp, Warning, TEXT("My Tank died!!!"))
}



