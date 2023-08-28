// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "TankStatics.h"

// Sets default values
ASpawner::ASpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 2.f;
	NoSpawnRange = 700.f;

	SpawnVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("SpawnVolume"));
	FVector BoxExtent = SpawnVolume->GetUnscaledBoxExtent();
	BoxExtent.Z = 100.f;
	SpawnVolume->SetBoxExtent(BoxExtent, false);
	if (RootComponent)
	{
		SpawnVolume->SetupAttachment(RootComponent);
	}
	else
	{
		RootComponent = SpawnVolume;
	}

	SpawnCollisionProfile = TEXT("Spawner:Block");
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();
	UTankStatics::PutInZPlane(this);

	Tank = Cast<ATank>(GetParentComponent()->GetOwner());
}

// Called every frame
void ASpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (ActorToSpawn)
	{
		if (UWorld* World = GetWorld())
		{
			FCollisionShape CollisionShape;
			CollisionShape.SetBox(FVector3f(SpawnVolume->GetUnscaledBoxExtent().X, SpawnVolume->GetUnscaledBoxExtent().Y, SpawnVolume->GetUnscaledBoxExtent().Z));
			if (!World->OverlapAnyTestByProfile(SpawnVolume->GetComponentLocation(), SpawnVolume->GetComponentRotation().Quaternion(), SpawnCollisionProfile, CollisionShape))
			{
				FVector SpawnLoc = FVector(UKismetMathLibrary::RandomPointInBoundingBox(SpawnVolume->GetComponentLocation(), SpawnVolume->GetUnscaledBoxExtent()));
				FVector const* SpawnLocRef = &SpawnLoc;
				if (AActor* SpawnedActor = World->SpawnActor(ActorToSpawn->GetDefaultObject()->GetClass(), SpawnLocRef))
				{
					if (Tank != NULL)
					{
						while (true)
						{
							SpawnedActor->SetActorLocation(UKismetMathLibrary::RandomPointInBoundingBox(SpawnVolume->GetComponentLocation(), SpawnVolume->GetUnscaledBoxExtent()));
							float DistSqXY = FVector::DistSquaredXY(Tank->GetActorLocation(), SpawnedActor->GetActorLocation());
							if (DistSqXY > (NoSpawnRange * NoSpawnRange))break;
						}
					}
					UTankStatics::PutInZPlane(SpawnedActor);
				}
			}
		}
	}
}

