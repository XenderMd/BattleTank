// Copyright EnderIT Ltd.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/PhysicsEngine/PhysicsConstraintComponent.h"
#include "Runtime/Engine/Classes/Components/SphereComponent.h"
#include "SprungWheel.generated.h"

UCLASS()
class BATTLETANK_API ASprungWheel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASprungWheel();

	void AddDrivingForce(float ForceMagnitude);

	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetupConstraint();

private:

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USphereComponent *Wheel = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	USphereComponent *Axle = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UPhysicsConstraintComponent *MassWheelConstraint = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UPhysicsConstraintComponent *AxleWheelConstraint = nullptr;
};
