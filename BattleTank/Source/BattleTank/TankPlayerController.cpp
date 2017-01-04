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
}
