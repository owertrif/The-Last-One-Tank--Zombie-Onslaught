// Fill out your copyright notice in the Description page of Project Settings.


#include "Barrel.h"

// Sets default values
ABarrel::ABarrel()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = BarrelDirection = CreateDefaultSubobject<UArrowComponent>("BarrelDirection");

	BarrelSprite = CreateDefaultSubobject<UPaperSpriteComponent>("BarrelSprite");
	BarrelSprite->SetupAttachment(BarrelDirection);
}

// Called when the game starts or when spawned
void ABarrel::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABarrel::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABarrel::SetupAttachment(USceneComponent* InParent)
{
	this->SetupAttachment(InParent);
}

UPaperSpriteComponent* ABarrel::GetBarrelSprite()
{
	return BarrelSprite;
}

