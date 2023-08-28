// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "Barrel.h"
#include "Turret.generated.h"

class AMissle;

UCLASS()
class TANKVSZOMBIES_API ATurret : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATurret();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	FORCEINLINE UArrowComponent* GetTurretDirection() { return TurretDirection; }

	UFUNCTION(BlueprintCallable, Category = "Crosshair")
	void SetCrosshairLoc(FVector Loc) { CrosshairLoc = Loc; }

	UFUNCTION(BlueprintCallable, Category = "Crosshair")
	void SetFire1CoolDown(float CoolDown) { Fire1CoolDown = CoolDown; };

	UFUNCTION(BlueprintCallable, Category = "Crosshair")
	float GetFire1CoolDown() { return Fire1CoolDown; };

	UFUNCTION(BlueprintCallable, Category = "Turret")
	FUpgrades_List GetUpgrades();
protected:
	//Max turn rate in degrees/second
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret")
		float YawSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret")
	ATank* Tank;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret")
	TArray<TSubclassOf<AActor>> Projectiles;

private:
	FVector CrosshairLoc;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Tank", meta = (AllowPrivateAccess = "true"))
	UChildActorComponent* ChildBarrel;

	//Helping to guess witch direction turret is facing
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
		UArrowComponent* TurretDirection;

	//Sprite of the turret
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
		UPaperSpriteComponent* TurretSprite;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
		float FireReadyTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Turret", meta = (AllowPrivateAccess = "true"))
		float Fire1CoolDown;
};

