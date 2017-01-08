// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "BattleTank.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


void UTankAimingComponent::SetBarrelReference(UTankBarrel * BarrelToSet) {
	Barrel = BarrelToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed) {
	if(Barrel){
		auto TankName = GetOwner()->GetName();
		auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FVector LaunchVelocity;

		if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, StartLocation, HitLocation, LaunchSpeed, ESuggestProjVelocityTraceOption::DoNotTrace)) {
			auto AimDirection = LaunchVelocity.GetSafeNormal();
			UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s"), *TankName, *AimDirection.ToString());
			MoveBarrelTowards(AimDirection);
		}
				
	}	
}

void UTankAimingComponent::MoveBarrelTowards(FVector Direction) {
	///move the turret rotation in the x and y plane so that it matches the ones in the vector passed in
	///move the barrel in the z direction so that the rotation matches the one passed in by the vector

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = Direction.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	Barrel->Elevate(5);///TODO remove magic number
}
