// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();	
	AimingComponent = GetPawn()->FindComponentByClass<UTankAimingComponent>();

	if (ensure(AimingComponent)) {
		FoundAimingComponent(AimingComponent);
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Player controller cannot find aiming component!"))
	}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

void ATankPlayerController::AimTowardsCrosshair(){
	if (!GetPawn()) { return; }
	if (!ensure(AimingComponent)) { return; }

	FVector HitLocation; //Out parameter
	if (GetSightRayHitLocation(HitLocation)) {
		AimingComponent->AimAt(HitLocation);
	}
}

bool ATankPlayerController::GetSightRayHitLocation(FVector &Location) const {
	
	///find crosshair in pixel coordinates
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	FVector2D ScreenLocation = FVector2D((ViewPortSizeX * CrossHairXLocation),(ViewPortSizeY *CrossHairYLocation));
	
	
	FVector WorldDirection;
	if (GetLookDirection(ScreenLocation, WorldDirection)) {				
		return GetLookVectorHitLocation(WorldDirection, Location);		
	}
	return false;
}

//Deproject the screen position of crosshair to world direction
bool ATankPlayerController::GetLookDirection(FVector2D ScreenLocation, FVector &LookDirection) const {
	FVector CameraLocation;		
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, CameraLocation, LookDirection);
}

bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const {
	FHitResult HitResult;
	FVector TraceStart = PlayerCameraManager->GetCameraLocation();
	FVector TraceEnd = TraceStart + LookDirection* LineTraceRange;
	
	///Line trace out and if hit set location and return true
	if (GetWorld()->LineTraceSingleByChannel(
		HitResult,
		TraceStart,
		TraceEnd,
		ECC_Visibility)) {
		HitLocation = HitResult.Location;
		return true;
	}

	///failed
	HitLocation = FVector(0);
	return false;
}


