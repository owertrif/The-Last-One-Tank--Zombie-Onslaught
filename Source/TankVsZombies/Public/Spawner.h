// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Tank.h"
#include "Spawner.generated.h"

UCLASS()
class TANKVSZOMBIES_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> ActorToSpawn;

	UPROPERTY(EditAnywhere)
	FName SpawnCollisionProfile;

	UPROPERTY(EditAnywhere)
	float NoSpawnRange;

	UPROPERTY(EditAnywhere)
	UBoxComponent* SpawnVolume;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Spawner")
	ATank* Tank;
};
