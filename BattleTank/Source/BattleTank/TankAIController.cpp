// Fill out your copyright notice in the Description page of Project Settings.

#include "BattleTank.h"
#include "TankAimingComponent.h"
#include "TankAIController.h"

void ATankAIController::BeginPlay() {
	Super::BeginPlay();
	ControlledTank = GetPawn();
	PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	TankAimingComponent = ControlledTank->FindComponentByClass<UTankAimingComponent>();
}

// Called every frame
void ATankAIController::Tick(float DeltaTime) {
	Super::Tick(DeltaTime);
	
	if (!ensure(PlayerTank && ControlledTank)) { return; }
		
	//move towards player
	MoveToActor(PlayerTank, AcceptanceRadius);

	//aim towards player amd fire		
	TankAimingComponent->AimAt(PlayerTank->GetActorLocation());
	TankAimingComponent->Fire();
	
}
