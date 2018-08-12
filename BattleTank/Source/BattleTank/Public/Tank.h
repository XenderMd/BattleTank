// Copyright EnderIT Ltd.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "GameFramework/Pawn.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "Tank.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE(FTankDelegate);


UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()


private:
	// Sets default values for this pawn's properties
	ATank();
	
	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:	

	virtual void BeginPlay() override;
	
	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor* DamageCauser) override;
	
	UFUNCTION (BlueprintPure, Category="Health")
	float GetHealthPercent();

	FTankDelegate OnDeath;
};
