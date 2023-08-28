



// Fill out your
#include "Upgrade.h"

// Sets default values
AUpgrade::AUpgrade()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>("RootComponent");
	}
	UpgradeSprite = CreateDefaultSubobject<UPaperSpriteComponent>("UpgradeSprte");

	Level = 0;
}

// Called when the game starts or when spawned
void AUpgrade::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AUpgrade::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

