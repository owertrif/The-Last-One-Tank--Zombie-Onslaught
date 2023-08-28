// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"
#include "TankGameMode.h"
#include "PaperFlipbookComponent.h"
#include "Upgrade.h"
#include "TankStatics.generated.h"

class ATank;

UENUM(BlueprintType)
enum class UpgradeType : uint8
{
	FuelTank,
	SteelPlate,
	WD40,
	GunPowder,
	Cooler,
	Wrench,
	AmmoScheme,
	NUM_OF_UPGRADES
};

USTRUCT(BlueprintType)
struct FUpgradeStruct {
GENERATED_BODY() 
public:
	UpgradeType Type;
	FString Description;
};
/**
 * 
 */
UCLASS()
class TANKVSZOMBIES_API UTankStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:
		//Calculate angle difference in the range [-180, 180].
		UFUNCTION(BlueprintCallable, Category = "Math")
		static float FindDeltaAngleDegrees(float A1, float A2);

		//Finds the angle between two 2d points
		UFUNCTION(BlueprintPure, Category = "Math|Rotator", meta = (Keywords = "rotation rotate"))
		static bool FindLookAtAngle2D(const FVector2D& Start, const FVector2D& Target, float& Angle);

		/** Get the current game mode, pre-cast to ATanksGameMode for convenience. */
		UFUNCTION(BlueprintCallable, Category = "Tanks")
		static class ATankGameMode* GetTanksGameMode(UObject* WorldContextObject);

		/** Snap this actor to the Z plane that we're using for this level. */
		UFUNCTION(BlueprintCallable, Category = "Tanks")
		static void PutInZPlane(AActor* ActorToMove);

		UFUNCTION(BlueprintCallable, Category = "Animation")
		static void PlayFlipbook(class UPaperFlipbookComponent* Component, class UPaperFlipbook* NewFlipbook, bool bLooping, float PlayRate = 1.0f, bool bPlayFromStart = false);

		UFUNCTION(BlueprintCallable, Category = "Upgrade")
		static FUpgradeStruct GetRandomUpgrade(ATank* Tank, TArray<int32> ExistingUpgrades);

		UFUNCTION(BlueprintCallable, Category = "Upgrade")
		static FString GetText(FUpgradeStruct upgrade) { return upgrade.Description; };
		UFUNCTION(BlueprintCallable, Category = "Upgrade")
		static int32 GetType(FUpgradeStruct upgrade) { return int32(upgrade.Type); };
};
