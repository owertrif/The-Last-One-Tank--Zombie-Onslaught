// Fill out your copyright notice in the Description page of Project Settings.


#include "Crosshair.h"

// Sets default values
ACrosshair::ACrosshair()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MaxCrosshairAimDistance = 300.f;
	AimingSpeed = 900.f;
}

// Called when the game starts or when spawned
void ACrosshair::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACrosshair::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

