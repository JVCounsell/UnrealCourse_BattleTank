// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	auto ControlledTank = GetControlledTank();
	auto PlayerTank = GetPlayerTank();

	if (PlayerTank) {
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI controller could not find a player"))
	}
}

// Called every frame
void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	if (GetPlayerTank()) {
		GetControlledTank()->AimAt(GetPlayerTank()->GetActorLocation());
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
