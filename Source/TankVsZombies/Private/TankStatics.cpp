// Fill out your copyright notice in the Description page of Project Settings.

#include "TankStatics.h"
#include "Tank.h"

float UTankStatics::FindDeltaAngleDegrees(float A1, float A2)
{
	 //Find the difference
	float Delta = A2 - A1;

	if (Delta > 180.f)
	{
		Delta = Delta - 360.f;
	}
	else if (Delta < -180.f)
	{
		Delta = Delta + 360.f;
	}

	return Delta;
}

bool UTankStatics::FindLookAtAngle2D(const FVector2D& Start, const FVector2D& Target, float& Angle)
{
	FVector2D Normal = (Target - Start).GetSafeNormal();
	if (!Normal.IsNearlyZero())
	{
		Angle = FMath::RadiansToDegrees(FMath::Atan2(Normal.Y, Normal.X));
		return true;
	}
	return false;
}

ATankGameMode* UTankStatics::GetTanksGameMode(UObject* WorldContextObject)
{
	return Cast<ATankGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
}

void UTankStatics::PutInZPlane(AActor* ActorToMove)
{
	if (ATankGameMode* GM = UTankStatics::GetTanksGameMode(ActorToMove))
	{
		FVector Loc = ActorToMove->GetActorLocation();
		Loc.Z = 130.f;
		ActorToMove->SetActorLocation(Loc);
	}
}

void UTankStatics::PlayFlipbook(UPaperFlipbookComponent* Component, UPaperFlipbook* NewFlipbook, bool bLooping, float PlayRate /*= 1.0f*/, bool bPlayFromStart /*= false*/)
{
	Component->SetFlipbook(NewFlipbook);
	Component->SetLooping(bLooping);
	Component->SetPlayRate(PlayRate);
	if (bPlayFromStart)
	{
		Component->PlayFromStart();
	}
	else
	{
		Component->Play();
	}
}

FUpgradeStruct UTankStatics::GetRandomUpgrade(ATank* Tank, TArray<int32> ExistingUpgrades)
{
	FUpgradeStruct upgrade;
	upgrade.Type = UpgradeType(FMath::RandRange(0, int(UpgradeType::NUM_OF_UPGRADES)-1));
	bool Unique = false;
	bool Allowed = false;

	while ( !Allowed)
	{
		while (true)
		{
			if (ExistingUpgrades[0] != int32(upgrade.Type) && ExistingUpgrades[1] != int32(upgrade.Type)) break;
			upgrade.Type = UpgradeType(FMath::RandRange(0, int(UpgradeType::NUM_OF_UPGRADES) - 1));
		}
		

		switch (upgrade.Type)
		{
		case UpgradeType::FuelTank:
			upgrade.Description = "Fuel tank - additional 10% to movement speed";
			if (Tank->GetUpgrades().FuelTank_Level == 5)
			{
				upgrade.Type = UpgradeType(FMath::RandRange(0, int(UpgradeType::NUM_OF_UPGRADES) - 1));
			}
			else
			{
				Allowed = true;
			}
			break;
		case UpgradeType::SteelPlate:
			upgrade.Description = "Steel plate - additional 5% to armor";
			if (Tank->GetUpgrades().SteelPlate_Level == 5)
			{
				upgrade.Type = UpgradeType(FMath::RandRange(0, int(UpgradeType::NUM_OF_UPGRADES) - 1));
			}
			else
			{
				Allowed = true;
			}
			break;
		case UpgradeType::WD40:
			upgrade.Description = "WD-40 - additional 5% to turret rotation speed";
			if (Tank->GetUpgrades().WD40_Level == 5)
			{
				upgrade.Type = UpgradeType(FMath::RandRange(0, int(UpgradeType::NUM_OF_UPGRADES) - 1));
			}
			else
			{
				Allowed = true;
			}
			break;
		case UpgradeType::GunPowder:
			upgrade.Description = "GunPowder - additional 7% to damage";
			if (Tank->GetUpgrades().Gunpowder_Level == 5)
			{
				upgrade.Type = UpgradeType(FMath::RandRange(0, int(UpgradeType::NUM_OF_UPGRADES) - 1));
			}
			else
			{
				Allowed = true;
			}
			break;
		case UpgradeType::Cooler:
			upgrade.Description = "Cooler - additional 10% to fire rate";
			if (Tank->GetUpgrades().Cooler_Level == 5)
			{
				upgrade.Type = UpgradeType(FMath::RandRange(0, int(UpgradeType::NUM_OF_UPGRADES) - 1));
			}
			else
			{
				Allowed = true;
			}
			break;
		case UpgradeType::Wrench:
			upgrade.Description = "Wrench - additional 10 HP";
			if (Tank->GetUpgrades().Wrench_Level == 5)
			{
				upgrade.Type = UpgradeType(FMath::RandRange(0, int(UpgradeType::NUM_OF_UPGRADES) - 1));
			}
			else
			{
				Allowed = true;
			}
			break;
		case UpgradeType::AmmoScheme:
			upgrade.Description = "Ammo scheme - additional 10% to size of projectiles";
			if (Tank->GetUpgrades().AmmoScheme_Level == 5)
			{
				upgrade.Type = UpgradeType(FMath::RandRange(0, int(UpgradeType::NUM_OF_UPGRADES) - 1));
			}
			else
			{
				Allowed = true;
			}
			break;
		default:
			break;
		}
	}
	
	return upgrade;
}