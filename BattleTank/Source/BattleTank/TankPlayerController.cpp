// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankPlayerController.h"

void ATankPlayerController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();	

	if (ControlledTank) {
		UE_LOG(LogTemp, Warning, TEXT("%s is the posessed tank"), *ControlledTank->GetName());
	}	else {
		UE_LOG(LogTemp, Warning, TEXT("Player controller not possesing a tank"))
	}
}

// Called every frame
void ATankPlayerController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	AimTowardsCrosshair();
}

ATank* ATankPlayerController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimTowardsCrosshair(){
	if (!GetControlledTank()) { return; }

	FVector HitLocation; //Out parameter
	if(GetSightRayHitLocation(HitLocation)){}

}

bool ATankPlayerController::GetSightRayHitLocation(FVector &Location) const {
	
	///find crosshair in pixel coordinates
	int32 ViewPortSizeX, ViewPortSizeY;
	GetViewportSize(ViewPortSizeX, ViewPortSizeY);
	FVector2D ScreenLocation = FVector2D((ViewPortSizeX * CrossHairXLocation),(ViewPortSizeY *CrossHairYLocation));
	
	Location = FVector(1.0f);
	return false;
}


