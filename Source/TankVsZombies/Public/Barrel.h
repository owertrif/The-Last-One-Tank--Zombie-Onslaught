// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PaperSpriteComponent.h"
#include "Components/ArrowComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Barrel.generated.h"

UCLASS()
class TANKVSZOMBIES_API ABarrel : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABarrel();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void SetupAttachment(USceneComponent* InParent);

	FORCEINLINE UArrowComponent* GetBarrelDirection() { return BarrelDirection; }

	UFUNCTION(BlueprintCallable, Category = "Sprite")
	UPaperSpriteComponent* GetBarrelSprite();
private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Barrel", meta = (AllowPrivateAccess = "true"))
		UArrowComponent* BarrelDirection;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Barrel", meta = (AllowPrivateAccess = "true"))
		UPaperSpriteComponent* BarrelSprite;
};
