// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "TankAIController.generated.h"

class ATank;

UCLASS()
class BATTLETANK_API ATankAIController : public AAIController
{
	
	GENERATED_BODY()

private:
	ATank* ControlledTank = nullptr;

	void BeginPlay() override;

	ATank* PlayerTank = nullptr;

	virtual void Tick(float DeltaSeconds) override;

	UPROPERTY(EditDefaultsOnly)
	float AcceptanceRadius = 3000.0f;
};
