// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TurretComponent.h"


void UTurretComponent::MoveTurret(float RelativeSpeed) {
	RelativeSpeed = FMath::Clamp(RelativeSpeed, -1.f, 1.f);
	auto AzimuthChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto Azimuth = RelativeRotation.Yaw + AzimuthChange;
	
	SetRelativeRotation(FRotator(0, Azimuth, 0));
}

