// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "UDamageInterface.generated.h"

UENUM(BlueprintType)
enum class EDamageType : uint8
{
	Unknown,
	HitWithMissle,
	Crushed,
	ZombieSplap,
	NumberOfEnums
};

UINTERFACE(MinimalAPI)
class UDamageInterface : public UInterface
{
	GENERATED_UINTERFACE_BODY()
};

class TANKVSZOMBIES_API IDamageInterface
{
	GENERATED_IINTERFACE_BODY()

public:
	virtual void ReceiveDamage(float IncomingDamage, EDamageType DamageType) = 0;
	virtual float GetHealthRemaining() = 0;
};
