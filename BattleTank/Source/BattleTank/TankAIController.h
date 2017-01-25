// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	
	GENERATED_BODY()

private:

	UTankAimingComponent* TankAimingComponent = nullptr;

	APawn* ControlledTank = nullptr;

	void BeginPlay() override;

	APawn* PlayerTank = nullptr;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 3000.0f;
};
