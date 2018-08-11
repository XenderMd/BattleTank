// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include"Runtime/Engine/Classes/Particles/ParticleSystemComponent.h"
#include "Runtime/Engine/Classes/PhysicsEngine/RadialForceComponent.h"
#include "Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "Runtime/Engine/Classes/Engine/World.h"
#include "GameFramework/Actor.h"
#include "Projectile.generated.h"

UCLASS()
class BATTLETANK_API AProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AProjectile();
	void LaunchProjectile(float LaunchSpeed);

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float DestroyDelay = 2.0;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
	float ProjectileDamage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY (VisibleAnywhere, Category = "Component")
	UStaticMeshComponent *CollisionMesh= nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UStaticMeshComponent *Sphere = nullptr;
	
	UPROPERTY(VisibleAnywhere, Category = "Component")
	UParticleSystemComponent *LaunchBlast= nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	UParticleSystemComponent *ImpactBlast = nullptr;

	UPROPERTY(VisibleAnywhere, Category = "Component")
	URadialForceComponent *ExplosionForce = nullptr;

private:
	UProjectileMovementComponent *ProjectileMovement = nullptr;
	
	UFUNCTION()
	void OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit);
	void DestroyProjectile();
};
