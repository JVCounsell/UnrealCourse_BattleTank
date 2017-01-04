// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();

	if (PlayerTank) {
		UE_LOG(LogTemp, Warning, TEXT("Ai controller found %s as a player"), *PlayerTank->GetName());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI controller could not find a player"))
	}
}

ATank * ATankAIController::GetPlayerTank() const {
	auto PTankController = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PTankController) {return nullptr;}
	return Cast<ATank>(PTankController);
}

ATank* ATankAIController::GetControlledTank() const {
	return Cast<ATank>(GetPawn());
}
