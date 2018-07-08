// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTracks.h"

UTankTracks:: UTankTracks()
{
	
}

void UTankTracks::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTracks::OnHit);
}

void UTankTracks::OnHit(UPrimitiveComponent * HitComponent, AActor * OtherActor, UPrimitiveComponent *OtherComp, FVector NormalImpulse, const FHitResult &Hit)
{
	UE_LOG(LogTemp, Warning, TEXT("Hit event is fired"))
}

// Bug Fix - since we removed previously the TickComponent, we had to explicitly Register this component again, to enable the Ticking (Lessons Q&A)
void  UTankTracks::OnRegister()
{
	Super::OnRegister();
	PrimaryComponentTick.bCanEverTick = true;
}

void UTankTracks::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	auto TankVelocity = GetOwner()->GetVelocity();
	auto TankSideMove = GetOwner()->GetActorRightVector();
	auto SlippageSpeed = FVector::DotProduct(TankVelocity, TankSideMove);

	auto CorrectionAcceleration = -SlippageSpeed / DeltaTime * TankSideMove;

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto CorrectionForce = (TankRoot->GetMass()*CorrectionAcceleration) / 2; // Two Tracks
	TankRoot->AddForce(CorrectionForce);
}

void UTankTracks::SetThrottle(float Throttle)
{
	
	//TODO - clamp the throttle values so that the player cannot overdrive
	auto ForceApplied = GetForwardVector()*Throttle*TrackMaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);

}


