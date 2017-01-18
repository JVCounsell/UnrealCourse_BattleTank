// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "Tank.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	ControlledTank = Cast<ATank>(GetPawn());;
	PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
}

// Called every frame
void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	if (PlayerTank) {
		//move towards player
		MoveToActor(PlayerTank, AcceptanceRadius);

		//aim towards player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());
		ControlledTank->Fire();
	}	
	else {
		UE_LOG(LogTemp, Warning, TEXT("AI controller could not find a player"))
	}
}
