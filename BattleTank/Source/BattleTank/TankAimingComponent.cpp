// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankBarrel.h"
#include "TurretComponent.h"
#include "Projectile.h"
#include "TankAimingComponent.h"


// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UTankAimingComponent::BeginPlay() {
	Super::BeginPlay();
	LastFireTime = FPlatformTime::Seconds();
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction) {
	if (ammoLeft > 0) {
		if ((FPlatformTime::Seconds() - LastFireTime) < ReloadTimeInSeconds) {
			FiringState = EFiringState::Reloading;
		}
		else if (IsBarrelMoving()) {
			FiringState = EFiringState::Aiming;
		}
		else {
			FiringState = EFiringState::Locked;
		}
	}
	else {
		FiringState = EFiringState::OutofAmmo;
	}
	
}

EFiringState UTankAimingComponent::GetFiringState() const {
	return FiringState;
}

int32 UTankAimingComponent::GetAmmoLeft() const {
	return ammoLeft;
}

void UTankAimingComponent::Initialize(UTankBarrel * BarrelToSet, UTurretComponent * TurretToSet) {
	Barrel = BarrelToSet;
	Turret = TurretToSet;
}

void UTankAimingComponent::AimAt(FVector HitLocation) {
	if(ensure(Barrel)){
		auto TankName = GetOwner()->GetName();
		auto StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
		FVector LaunchVelocity;

		if (UGameplayStatics::SuggestProjectileVelocity(this, LaunchVelocity, StartLocation, HitLocation, LaunchSpeed, false, 0, 0, ESuggestProjVelocityTraceOption::DoNotTrace)) {
			AimDirection = LaunchVelocity.GetSafeNormal();
			MoveBarrelTowards(AimDirection);
			MoveTurretTowards(AimDirection);
		}
				
	}	
}

void UTankAimingComponent::MoveBarrelTowards(FVector Direction) {
	if (!ensure(Barrel && Turret)){ return; }
	///move the barrel in the z direction so that the rotation matches the one passed in by the vector

	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = Direction.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;
		
	Barrel->Elevate(DeltaRotator.Pitch);
}

void UTankAimingComponent::MoveTurretTowards(FVector Direction) {
	if (!ensure(Turret)) { return; }
	///move the barrel in the z direction so that the rotation matches the one passed in by the vector

	auto TurretRotator = Turret->GetForwardVector().Rotation();
	auto AimAsRotator = Direction.Rotation();
	auto DeltaRotator = AimAsRotator - TurretRotator;
	
	// always the shortest route
	if (FMath::Abs(DeltaRotator.Yaw)< 180) {
		Turret->MoveTurret(DeltaRotator.Yaw);
	}
	else {
		Turret->MoveTurret(-DeltaRotator.Yaw);
	}
}

bool UTankAimingComponent::IsBarrelMoving() {
	if (!ensure(Barrel)) { return false; }
	auto BarrelForwardVector = Barrel->GetForwardVector();
	return !BarrelForwardVector.Equals(AimDirection, 0.01);
}
	

void UTankAimingComponent::Fire() {	
	if (FiringState != EFiringState::Reloading && ammoLeft > 0) {
		if (!ensure(Barrel)) { return; }
		if (!ensure(ProjectileBlueprint)) { return; }
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(ProjectileBlueprint, Barrel->GetSocketLocation("Projectile"), Barrel->GetSocketRotation("Projectile"));
		Projectile->LaunchProjectile(LaunchSpeed);
		LastFireTime = FPlatformTime::Seconds();
		ammoLeft -=1;
	}
}

