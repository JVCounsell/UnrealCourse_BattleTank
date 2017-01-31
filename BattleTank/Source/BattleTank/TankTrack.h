// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * Tank Track is used to set maximum driving force, andto apply forces to the tank.
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class BATTLETANK_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	// sets a value between 1 and -1
	UFUNCTION(BlueprintCallable, Category = "Input")
	void SetThrottle(float Throttle);
	
	//Max force per track in Newtons
	UPROPERTY(EditDefaultsOnly)
	float MaxDrivingForce = 40000000; //Assume 40 tonne tank, 1G Acceleration

private:
	UTankTrack();

	virtual void BeginPlay() override;

	void ApplySidewaysForce();

	UFUNCTION(BlueprintCallable, Category = "Collision")
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComponent, FVector NormalImpulse, const FHitResult& Hit);
	
	void DriveTrack();

	float CurrentThrottle = 0;
};
