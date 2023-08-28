// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PaperSpriteComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "UDamageInterface.h"
#include "TankStatics.h"
#include "Components/BoxComponent.h"
#include "Tank.generated.h"

//This struct covers all posible tank input schemes.
USTRUCT(BlueprintType)
struct FTankInput {
	GENERATED_BODY()
public:
	//sanitized movemetn input,ready to be used by game logic.
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank Input")
	FVector2D MovementInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank Input")
	FVector2D AimingInput;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank Input")
		uint32 bFire1 : 1;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank Input")
		uint32 bFire2 : 1;

	void Sanitize();
	void MoveX(float AxisVal);
	void MoveY(float AxisVal);
	void AimX(float AxisVal);
	void AimY(float AxisVal);

private:
	//Private because its internal, raw data. Game code should never see this.
	FVector2D RawMovementInput;
	FVector2D RawAimingInput;
};

USTRUCT(BlueprintType)
struct FUpgrades_List {
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Upgrades list")
	int32 FuelTank_Level ;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Upgrades list")
	int32 WD40_Level ;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Upgrades list")
	int32 SteelPlate_Level ;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Upgrades list")
	int32 Wrench_Level ;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Upgrades list")
	int32 Gunpowder_Level ;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Upgrades list")
	int32 Cooler_Level ;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Upgrades list")
	int32 AmmoScheme_Level;
};

UCLASS()
class TANKVSZOMBIES_API ATank : public APawn, public IDamageInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "Input")
	const FTankInput& GetCurrentInput() { return TankInput; }

	//~ Begin IDamageInterface
	virtual void ReceiveDamage(float IncomingDamage, EDamageType DamageType) override;
	virtual float GetHealthRemaining()override { return Health; };
	//~ End IDamageInterface

	UFUNCTION(BlueprintNativeEvent, Category = "Tank")
	void TankDie(EDamageType DamageType);

	UFUNCTION(BlueprintNativeEvent, Category = "Tank")
	void LevelUp();

	UFUNCTION(BlueprintCallable, Category = "LevelUp")
	void RecieveXp(float RecievedXp);

	UFUNCTION(BlueprintCallable, Category = "LevelUp")
	void AddLevelToUpgrade(UpgradeType type, int32 lvl);

	UFUNCTION(BlueprintCallable, Category = "Upgrades")
	FUpgrades_List GetUpgrades() { return Upgrades; }
private:
	void MoveX(float AxisVal);
	void MoveY(float AxisVal);
	void AimX(float AxisVal);
	void AimY(float AxisVal);

private:
	//Helping to guess witch direction tank is facing
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UArrowComponent* TankDirection;
	
	//Collision box for Tank
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UBoxComponent* TankBody;

	//Sprite of the tank body
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UPaperSpriteComponent* TankBodySprite;

	//The actor used as a turret
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* ChildTurret;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* ChildCrosshair;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* ChildSpawner;

	//Arm that connecting camera end tank
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	USpringArmComponent* SpringArm;

	//Actually the view
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UCameraComponent* Camera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	FUpgrades_List Upgrades;

protected:
	//Input struct.
	UPROPERTY(VisibleAnywhere, Category = "Tank input")
	FTankInput TankInput;

	//Maximum turn speed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tank", meta = (ClampMin = "0.0"))
	float YawSpeed;

	// Acceleration for our tank, when player is trying to move or change directions.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tank", meta = (ClampMin = "0.0"))
	float MoveAccel;

	//Maximum move speed
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tank", meta = (ClampMin = "0.0"))
	float MoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tank", meta = (ClampMin = "0.0"))
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tank", meta = (ClampMin = "0.0"))
	float MaxHealth;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tank", meta = (ClampMin = "0.0"))
	float Armor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tank", meta = (ClampMin = "0.0"))
	int32 TankLevel;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tank", meta = (ClampMin = "0.0"))
	float CurrentXp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tank", meta = (ClampMin = "0.0"))
	float NeededXp;

	// Collision profile for detecting (via overlaps) the things we can crush.
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Tank")
	FName CrushCollisionProfile;
};
