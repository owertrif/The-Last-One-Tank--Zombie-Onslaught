// Fill out your copyright notice in the Description page of Project Settings.

#include "Turret.h"
#include "Barrel.h"
#include "Crosshair.h"
#include "Missle.h"


// Sets default values
ATurret::ATurret()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = TurretDirection = CreateDefaultSubobject<UArrowComponent>("TurretDirection");
	
	TurretSprite = CreateDefaultSubobject<UPaperSpriteComponent>("TurretSprite");
	TurretSprite->SetupAttachment(TurretDirection);

	ChildBarrel = CreateDefaultSubobject<UChildActorComponent>("Barrel");
	ChildBarrel->SetupAttachment(TurretDirection);

	YawSpeed = 180.f;
	Fire1CoolDown = 2.f;
}

// Called when the game starts or when spawned
void ATurret::BeginPlay()
{
	Super::BeginPlay();
	Tank = Cast<ATank>(GetParentComponent()->GetOwner());
	//check(Tank);
}

// Called every frame
void ATurret::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//UE_LOG(LogTemp, Warning, TEXT("0"));
	check(TurretDirection);
	if (Tank != NULL)
	{
		if (APlayerController* PC = Cast<APlayerController>(Tank->GetController()))
		{
			FVector2D AimLocation;
			UGameplayStatics::ProjectWorldToScreen(PC, CrosshairLoc, AimLocation);

			FVector2D TurretLocation = FVector2D::ZeroVector;
			UGameplayStatics::ProjectWorldToScreen(PC, TurretDirection->GetComponentLocation(), TurretLocation);


			float DesiredYaw;

			if (UTankStatics::FindLookAtAngle2D(TurretLocation, AimLocation, DesiredYaw))
			{
				FRotator CurrentRotation = TurretDirection->GetComponentRotation();
				float DeltaYaw = UTankStatics::FindDeltaAngleDegrees(CurrentRotation.Yaw, DesiredYaw);
				float MaxDeltaYawThisFrame = (YawSpeed + YawSpeed * 0.05 *Tank->GetUpgrades().WD40_Level) * DeltaTime;
				if (MaxDeltaYawThisFrame >= FMath::Abs(DeltaYaw))
				{

						//We can get there on this frame, so just set it
					CurrentRotation.Yaw = DesiredYaw;

				}
				else
				{

					CurrentRotation.Yaw += FMath::Sign(DeltaYaw) * MaxDeltaYawThisFrame;

				}

				TurretDirection->SetWorldRotation(CurrentRotation);
			}
			const FTankInput& CurrentInput = Tank->GetCurrentInput();

			//Handle Input
			
			if (Projectiles.Num())
			{
				if (UWorld* World = GetWorld())
				{
					float CurrentTime = World->GetTimeSeconds();
					if (FireReadyTime <= CurrentTime)
					{
						if (ABarrel* Barrel = Cast<ABarrel>(ChildBarrel->GetChildActor()))
						{

							FVector Loc = Barrel->GetBarrelSprite()->GetSocketLocation("Muzzle");
							FRotator Rot = Barrel->GetBarrelDirection()->GetComponentRotation();

							for (TSubclassOf<AActor> Projectile : Projectiles)
							{
								if (AActor* NewProjectile = World->SpawnActor(Projectile))
								{
									NewProjectile->SetActorLocation(Loc);
									NewProjectile->SetActorRotation(Rot);
									if (AMissle* Missile = Cast<AMissle>(NewProjectile))
									{
										Missile->SetDamageBuff(Tank->GetUpgrades().Gunpowder_Level);
										Missile->SetSizeBuff(Tank->GetUpgrades().AmmoScheme_Level);
									}
								}
							}
						}
						FireReadyTime = CurrentTime + Fire1CoolDown;
					}
				}
			}
		}
	}
}

FUpgrades_List ATurret::GetUpgrades()
{
	return Tank->GetUpgrades();
}