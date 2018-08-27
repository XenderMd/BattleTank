// Copyright EnderIT Ltd.

#include "SprungWheel.h"


// Sets default values
ASprungWheel::ASprungWheel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	PhysicsConstraint=CreateDefaultSubobject<UPhysicsConstraintComponent>(FName("Physical Constraint"));
	SetRootComponent(PhysicsConstraint);

	Mass = CreateDefaultSubobject<UStaticMeshComponent>(FName("Mass"));
	Mass->AttachToComponent(PhysicsConstraint, FAttachmentTransformRules::KeepRelativeTransform);

	Wheel= CreateDefaultSubobject<UStaticMeshComponent>(FName("Wheel"));
	Wheel->AttachToComponent(PhysicsConstraint, FAttachmentTransformRules::KeepRelativeTransform);

}

// Called when the game starts or when spawned
void ASprungWheel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASprungWheel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

