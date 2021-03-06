// Copyright EnderIT Ltd.

#include "TankMovementComponent.h"
#include "TankTracks.h"


void UTankMovementComponent::Initialise(UTankTracks *LeftTrackToSet, UTankTracks *RightTrackToSet)
{
	LeftTrack = LeftTrackToSet;
	RightTrack = RightTrackToSet;
}

void UTankMovementComponent::IntendMoveStraight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}

void UTankMovementComponent::IntendTurnLeft(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(-Throw);
	RightTrack->SetThrottle(Throw);

}

void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}


void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super
	
	auto TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();
	auto AIForwadIntention = MoveVelocity.GetSafeNormal();


	auto ForwardThrow = FVector::DotProduct(TankForward, AIForwadIntention);
	IntendMoveStraight(ForwardThrow);

	auto RightThrow = FVector::CrossProduct(TankForward, AIForwadIntention).Z;
	IntendTurnRight(RightThrow);
	
}

