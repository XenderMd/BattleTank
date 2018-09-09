// Copyright EnderIT Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Projectile.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "AutoMortar.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FAutoMortarDelegate);

UCLASS()
class BATTLETANK_API AAutoMortar : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAutoMortar();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:

	UPROPERTY(EditDefaultsOnly, Category = "Health")
	int32 StartingHealth = 100;

	UPROPERTY(VisibleAnywhere, Category = "Health")
	int32 CurrentHealth;


public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const & DamageEvent, AController * EventInstigator, AActor* DamageCauser) override;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealthPercent();

	FAutoMortarDelegate OnDeath;	
};
