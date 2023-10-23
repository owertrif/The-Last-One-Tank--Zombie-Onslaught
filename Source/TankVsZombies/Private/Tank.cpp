// Fill out your copyright notice in the Description page of Project Settings.


#include "Tank.h"
#include "Crosshair.h"
#include "Turret.h"

void FTankInput::Sanitize()
{
	MovementInput = RawMovementInput.ClampAxes(-1.f, 1.f);
	MovementInput = MovementInput.GetSafeNormal();
	AimingInput = RawAimingInput.ClampAxes(-1.f, 1.f);
	AimingInput = AimingInput.GetSafeNormal();
	RawMovementInput.Set(0.f, 0.f);
	RawAimingInput.Set(0.f, 0.f);
}

void FTankInput::MoveX(float AxisVal)
{
	RawMovementInput.X += AxisVal;
}
void FTankInput::MoveY(float AxisVal)
{
	RawMovementInput.Y += AxisVal;
}

void FTankInput::AimX(float AxisVal)
{
	RawAimingInput.X += AxisVal;
}
void FTankInput::AimY(float AxisVal)
{
	RawAimingInput.Y += AxisVal;
}

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TankBodySprite = CreateDefaultSubobject<UPaperSpriteComponent>("BodySprite");
	TankDirection = CreateDefaultSubobject<UArrowComponent>("TankDirection");
	TankBody = CreateDefaultSubobject<UBoxComponent>(TEXT("TankBody"));

	if (!RootComponent)
	{
		RootComponent = CreateDefaultSubobject<USceneComponent>("TankBase");
	}

	TankDirection->SetupAttachment(RootComponent);
	TankBodySprite->SetupAttachment(TankDirection);
	TankBody->SetupAttachment(TankDirection);
	TankBody->SetBoxExtent(FVector(50.f, 50.f, 100.f));

	ChildTurret = CreateDefaultSubobject<UChildActorComponent>("Turret");
	ChildTurret->SetupAttachment(TankDirection);

	ChildCrosshair = CreateDefaultSubobject<UChildActorComponent>("Crosshair");
	ChildCrosshair->SetupAttachment(TankDirection);

	ChildSpawner = CreateDefaultSubobject<UChildActorComponent>("Spawner");
	ChildSpawner->SetupAttachment(TankDirection);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 500.f;
	SpringArm->bEnableCameraLag = true;
	SpringArm->bEnableCameraRotationLag = false;
	SpringArm->bUsePawnControlRotation = false;
	SpringArm->CameraLagSpeed = 2.f;
	SpringArm->bDoCollisionTest = false;
	SpringArm->SetWorldRotation(FRotator(0.0f, -90.0f, 0.0f));

	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->bUsePawnControlRotation = false;
	Camera->ProjectionMode = ECameraProjectionMode::Perspective;
	Camera->OrthoWidth = 1024.f;
	Camera->AspectRatio = 3.f / 4.f;
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->SetWorldRotation(FRotator(-90.0f, 0.0f, 0.0f));

	MoveSpeed = 100.f;
	MoveAccel = 200.f;
	YawSpeed = 120.f;
	MaxHealth = 100.f;
	Health = MaxHealth;
	Armor = 10.f;
	NeededXp = 100;
	CurrentXp = 0;
	TankLevel = 0;

	Upgrades.Cooler_Level = 0;
	Upgrades.FuelTank_Level = 0;
	Upgrades.SteelPlate_Level = 0;
	Upgrades.WD40_Level = 0;
	Upgrades.Wrench_Level = 0;
	Upgrades.Gunpowder_Level = 0;

	CrushCollisionProfile = TEXT("Tank:Crush");
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TankInput.Sanitize();
	//Move the tank!
	if(GetHealthRemaining() > 0)
	{
		FVector DesiredMovementDirection = FVector(TankInput.MovementInput.X, TankInput.MovementInput.Y, 0);
		if (!DesiredMovementDirection.IsNearlyZero())
		{
			//Rotate the tank ! Note that we rotate the tank TankDirection component,
			//not the RootComponent.
			FRotator MovementAngle = DesiredMovementDirection.Rotation();
			float DeltaYaw = UTankStatics::FindDeltaAngleDegrees(TankDirection->GetComponentRotation().Yaw, MovementAngle.Yaw);
			bool bReverse = false;
			if (DeltaYaw != 0.f)
			{
				float AdjustedDeltaYaw = DeltaYaw;

				if (AdjustedDeltaYaw < -90.f)
				{
					AdjustedDeltaYaw += 180.f;
					bReverse = true;
				}
				else if (AdjustedDeltaYaw > 90.f)
				{
					AdjustedDeltaYaw -= 180.f;
					bReverse = true;
				}
				//Turn torward the desired angle. stop if we can get there in one frame

				float MaxYawThisFrame = YawSpeed * DeltaTime;
				if (MaxYawThisFrame >= FMath::Abs(AdjustedDeltaYaw))
				{
					if (bReverse)
					{
						//Move backward
						FRotator FacingAngle = MovementAngle;
						FacingAngle.Yaw = MovementAngle.Yaw + 180.f;
						TankDirection->SetWorldRotation(FacingAngle);
					}
					else
					{
						TankDirection->SetWorldRotation(MovementAngle);
					}
				}
				else
				{
					//Cant reach our desired angle this frame, rotate part way.
					TankDirection->AddLocalRotation(FRotator(0.f,FMath::Sign(AdjustedDeltaYaw) * MaxYawThisFrame, 0.f));
				}

				
			}
			//Move the tank
			{
				FVector MovementDirection = TankDirection->GetForwardVector() * (bReverse ? -1.f : 1.f);
				FVector StartPos = GetActorLocation();
				FVector Pos = StartPos;
				Pos.X += MovementDirection.X * MoveSpeed * DeltaTime;
				Pos.Y += MovementDirection.Y * MoveSpeed * DeltaTime;

				if (UWorld* World = GetWorld())
				{
					TArray<FHitResult> HitResults;
					FVector3f BoxSize = FVector3f(TankBody->GetScaledBoxExtent().X, TankBody->GetScaledBoxExtent().Y, TankBody->GetScaledBoxExtent().Z);
					FCollisionShape CollisionShape;
					CollisionShape.SetBox(BoxSize);
					World->SweepMultiByProfile(HitResults, StartPos, Pos, TankBody->GetComponentRotation().Quaternion(), CrushCollisionProfile, CollisionShape);
					for (const FHitResult& HitResult : HitResults)
					{
						FString str = HitResult.GetActor()->GetActorLabel();
						if (IDamageInterface* DamageTarget = Cast<IDamageInterface>(HitResult.GetActor()))
						{
							int32 TargetHealth = DamageTarget->GetHealthRemaining();
							if (TargetHealth >= 0)
							{
								DamageTarget->ReceiveDamage(TargetHealth, EDamageType::Crushed);
							}
						}
						else if(str.Contains("BP_Wall"))
						{
							Pos.X -= MovementDirection.X * MoveSpeed * DeltaTime;
							Pos.Y -= MovementDirection.Y * MoveSpeed * DeltaTime;
						}
					}
				}

				SetActorLocation(Pos);
			}
		}

		//Aiming
		if (ACrosshair* Crosshair = Cast<ACrosshair>(ChildCrosshair->GetChildActor()))
		{
			if (ATurret* Turret = Cast<ATurret>(ChildTurret->GetChildActor()))
			{
				Turret->SetCrosshairLoc(Crosshair->GetActorLocation());
			}

			FVector DesiredAimingDirection = FVector(TankInput.AimingInput.X, TankInput.AimingInput.Y, 0.f);
			if (!DesiredAimingDirection.IsNearlyZero())
			{
				FVector DesiredCrosshairPos = Crosshair->GetActorLocation();
				DesiredCrosshairPos.X += DesiredAimingDirection.X * Crosshair->GetAimingSpeed() * DeltaTime;
				DesiredCrosshairPos.Y += DesiredAimingDirection.Y * Crosshair->GetAimingSpeed() * DeltaTime;
				float DesiredAimingDistance = FVector::Distance(GetActorLocation(), DesiredCrosshairPos);
				if (DesiredAimingDistance <= Crosshair->GetMaxCrosshairAimDistance())
				{
					
					Crosshair->SetActorLocation(DesiredCrosshairPos);
				}
				else
				{
					float xDiff = GetActorLocation().X - DesiredCrosshairPos.X;
					float yDiff = GetActorLocation().Y - DesiredCrosshairPos.Y;
					float multiplier = DesiredAimingDistance / Crosshair->GetMaxCrosshairAimDistance();
					DesiredCrosshairPos.X = GetActorLocation().X - xDiff / multiplier;
					DesiredCrosshairPos.Y = GetActorLocation().Y - yDiff / multiplier;
					Crosshair->SetActorLocation(DesiredCrosshairPos);
				}
			}
		}
	}
}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	InputComponent->BindAxis("MoveX", this, &ATank::MoveX);
	InputComponent->BindAxis("MoveY", this, &ATank::MoveY);
	InputComponent->BindAxis("AimX", this, &ATank::AimX);
	InputComponent->BindAxis("AimY", this, &ATank::AimY);
}

void ATank::RecieveXp(float RecievedXp)
{
	if (CurrentXp <= NeededXp)
	{
		CurrentXp += RecievedXp;
	}
	else
	{
		CurrentXp -= NeededXp;
		TankLevel++;
		NeededXp += 100 + 20 + TankLevel*0.5;
		LevelUp();
	}
}

void ATank::MoveX(float AxisVal)
{
	TankInput.MoveX(AxisVal);
}

void ATank::MoveY(float AxisVal)
{
	TankInput.MoveY(AxisVal);
}

void ATank::AimX(float AxisVal)
{
	TankInput.AimX(AxisVal);
}

void ATank::AimY(float AxisVal)
{
	TankInput.AimY(AxisVal);
}

void ATank::ReceiveDamage(float IncomingDamage, EDamageType DamageType)
{
	if (IncomingDamage >= Health)
	{
		if (Health - IncomingDamage <= 0)
		{
			Health = -1;
			TankDie(DamageType);
		}
		return;
	}
	Health -= (IncomingDamage - IncomingDamage*0.01*(Armor + Armor*0.05*Upgrades.SteelPlate_Level));
}

void ATank::TankDie_Implementation(EDamageType DamageType)
{
	
}

void ATank::LevelUp_Implementation()
{

}

void ATank::AddLevelToUpgrade(UpgradeType type, int32 lvl)
{
	ATurret* Turret = Cast<ATurret>(ChildTurret->GetChildActor());
	switch(type)
	{
	case UpgradeType::FuelTank:
		Upgrades.FuelTank_Level += lvl;
		MoveSpeed += MoveSpeed * 0.1;
		YawSpeed += YawSpeed * 0.05;
		break;
	case UpgradeType::SteelPlate:
		Upgrades.SteelPlate_Level += lvl;
		Armor += 5.f;
		break;
	case UpgradeType::WD40:
		Upgrades.WD40_Level += lvl;
		break;
	case UpgradeType::GunPowder:
		Upgrades.Gunpowder_Level += lvl;
		break;
	case UpgradeType::Cooler:
		Upgrades.Cooler_Level += lvl;
		Turret->SetFire1CoolDown(Turret->GetFire1CoolDown() - Turret->GetFire1CoolDown() * 0.1);
		break;
	case UpgradeType::Wrench:
		Upgrades.Wrench_Level += lvl;
		MaxHealth += 10.f;
		Health += 10.f;
		break;
	case UpgradeType::AmmoScheme:
		Upgrades.AmmoScheme_Level += lvl;
		break;
	default:
		break;
	}
}