// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "PaperFlipbookComponent.h"
#include "UDamageInterface.h"
#include "Missle.generated.h"

UCLASS()
class TANKVSZOMBIES_API AMissle : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMissle();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	float GetDamage() { return DirectDamage; };

	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SetDamageBuff(int32 lvl) { DamageBuff = lvl; };
	UFUNCTION(BlueprintCallable, Category = "Projectile")
	void SetSizeBuff(int32 lvl) { SizeBuff = lvl; };

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Speed;

	/** This missile's radius for collisions. If less than or equal to zero, missile will not check for collision. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float Radius;

	/** Damage inflicted on a direct hit. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float DirectDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float SplashDamage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	float SplashRadius;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	int32 DamageBuff;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	int32 SizeBuff;

	/** Describes what this missile hits. */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Projectile")
	FName MovementCollisionProfile;
protected:

	FTimerHandle ExplodeTimerHandle;
	bool isExploded;

	void Explode();

	UFUNCTION(BlueprintNativeEvent, Category = "Animation", meta = (Keywords = "explode"))
	void OnExplode();
};
