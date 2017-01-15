// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankTrack.h"

void UTankTrack::SetThrottle(float Throttle) {
	auto name = GetName();
	UE_LOG(LogTemp, Warning, TEXT("%s at %f"), *name, Throttle)
	Throttle = FMath::Clamp(Throttle, -1.f, 1.f);
	auto ForceApplied =GetForwardVector()* Throttle * MaxDrivingForce;
	auto ForceLocation = GetComponentLocation();
	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}


