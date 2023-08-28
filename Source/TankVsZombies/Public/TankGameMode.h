// Fill out your copyright notice in the Description page of Project Settings.

#pragma once


#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "TankGameMode.generated.h"

/**
 * 
 */
UCLASS()
class TANKVSZOMBIES_API ATankGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	ATankGameMode();

	UPROPERTY(EditAnywhere)
	float PlayInZPlane;
};
