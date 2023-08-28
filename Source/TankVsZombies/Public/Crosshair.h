// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Components/ArrowComponent.h"
#include "Tank.h"
#include "Crosshair.generated.h"

UCLASS()
class TANKVSZOMBIES_API ACrosshair : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACrosshair();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Crosshair")
	float GetMaxCrosshairAimDistance() { return MaxCrosshairAimDistance; }

	UFUNCTION(BlueprintCallable, Category = "Crosshair")
	float GetAimingSpeed() { return AimingSpeed; }

private:
	//Max distance between tank and crosshair
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Crosshair", meta = (AllowPrivateAccess = "true"))
		float MaxCrosshairAimDistance;

	//Max speed of croshair
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, Category = "Crosshair", meta = (AllowPrivateAccess = "true"))
		float AimingSpeed;
};
