// Fill out your copyright notice in the Description page of Project Settings.

#include "Missle.h"
#include "Turret.h"


// Sets default values
AMissle::AMissle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Speed = 200.f;
	Radius = 20.f;
	DirectDamage = 100.f;
	SplashRadius = 100.f;
	SplashDamage = DirectDamage * 0.4f;
	isExploded = false;
	MovementCollisionProfile = TEXT("NONE");
}

// Called when the game starts or when spawned
void AMissle::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(ExplodeTimerHandle, this, &AMissle::Explode, 2.0f);
}

// Called every frame
void AMissle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FVector Loc = GetActorLocation();
	FVector DesiredEndLoc = Loc + (DeltaTime * Speed) * GetTransform().GetUnitAxis(EAxis::X);
	FHitResult HitResult;
	FCollisionShape CollisionShape;
	if (Radius > 0.f && GetActorEnableCollision())
	{
		if (UWorld* World = GetWorld())
		{
			CollisionShape.SetCapsule(Radius + Radius*0.1f*SizeBuff, 200.f);
			if (World->SweepSingleByProfile(HitResult, Loc, DesiredEndLoc, FQuat::Identity, MovementCollisionProfile, CollisionShape))
			{
				SetActorLocation(HitResult.Location);
				if (IDamageInterface* DamageActor = Cast<IDamageInterface>(HitResult.GetActor()))
				{
					DamageActor->ReceiveDamage(DirectDamage + DirectDamage * 0.07 * DamageBuff, EDamageType::HitWithMissle);
				}
				TArray<FHitResult> HitResults;
				CollisionShape.SetCapsule(SplashRadius + SplashRadius*0.1f*SizeBuff, 200.f);
				World->SweepMultiByProfile(HitResults, Loc, DesiredEndLoc, GetActorRotation().Quaternion(), MovementCollisionProfile, CollisionShape);
				for (FHitResult Result : HitResults)
				{
					if (IDamageInterface* DamageActor = Cast<IDamageInterface>(Result.GetActor()))
					{
						DamageActor->ReceiveDamage(SplashDamage + SplashDamage*0.07*DamageBuff, EDamageType::HitWithMissle);
					}
				}

				Explode();
			}
			else
			{
				SetActorLocation(DesiredEndLoc);
			}
		}
	}
}

void AMissle::OnExplode_Implementation()
{
	Destroy();
}

void AMissle::Explode()
{
	GetWorldTimerManager().ClearTimer(ExplodeTimerHandle);
	isExploded = true;
	OnExplode();


}