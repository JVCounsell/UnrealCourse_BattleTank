// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TurretComponent.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet) {
	if (!BarrelToSet){ return; }
	Barrel = BarrelToSet;
}

void UTankAimingComponent::SetTurretReference(UTurretComponent * TurretToSet) {
	if (!TurretToSet){ return; }
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	if(Barrel){
		auto TankName = GetOwner()->GetName();
		auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FVector LaunchVelocity;

		if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
			auto AimDirection = LaunchVelocity.GetSafeNormal();
			UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *TankName, *AimDirection.ToString());
			MoveBarrelTowards(AimDirection);
			MoveTurretTowards(AimDirection);
		}
				
	}	
}

void UTankAimingComponent::MoveBarrelTowards(FVector Direction) {
	
	///move the barrel in the z direction so that the rotation matches the one passed in by the vector

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = Direction.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector Direction) {

	///move the barrel in the z direction so that the rotation matches the one passed in by the vector

	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = Direction.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;

	Turret->MoveTurret(DeltaRotator.Yaw);
}