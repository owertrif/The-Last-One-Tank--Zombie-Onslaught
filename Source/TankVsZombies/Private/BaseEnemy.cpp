// Fill out your copyright notice in the Description page of Project Settings.

#include "BaseEnemy.h"
#include "Tank.h"


// Sets default values
ABaseEnemy::ABaseEnemy()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Health = 100.f;
	AttackDamage = 10.f;
	AttackDistance = 100.f;
	AttackCooldown = 1.f;
	GivenXp = 10;
	EnemyCollisionProfile = TEXT("Zombie:General");

}

// Called when the game starts or when spawned
void ABaseEnemy::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABaseEnemy::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (GetCharacterMovement()->IsWalking() && !EnemyAIShouldAttack() && Health > 0)
	{
		float DistanceWalked = GetCharacterMovement()->Velocity.Length()*DeltaTime;
		EnemyWalk(DeltaTime, DistanceWalked);
	}
	
	FVector DirectToTarget = (TargetActor->GetActorLocation() - GetActorLocation()).GetSafeNormal2D();
	if (DirectToTarget.X < 0.f)
	{
		//Rotating enemy to face left
		SetActorRotation(FRotator(180, 0, 0));
	}
	else
	{
		//Rotating enemy to face right
		SetActorRotation(FRotator(0, 0, 0));
	}

	ConsumeAttackInput();
	ConsumeMovementInputVector();
	ConsumeRotationInput();
}

// Called to bind functionality to input
void ABaseEnemy::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void ABaseEnemy::SetTarget(AActor* NewTarget)
{
	TargetActor = NewTarget;
	TargetTank = Cast<ATank>(NewTarget);
}

AActor* ABaseEnemy::GetTarget()
{
	return TargetActor;
}

ATank* ABaseEnemy::GetTargetAsTank()
{
	return TargetTank;
}

float ABaseEnemy::GetAttackDistance()
{
	return AttackDistance;
}


void ABaseEnemy::AddRotationInput(float DeltaYawDegrees)
{
	YawInput += DeltaYawDegrees;
}

float ABaseEnemy::GetRotationInput()
{
	return YawInput;
}

float ABaseEnemy::ConsumeRotationInput()
{
	float RetVal = YawInput;
	YawInput = 0.0f;
	return RetVal;
}

void ABaseEnemy::AddAttackInput()
{
	bAttackInput = true;
}

bool ABaseEnemy::GetAttackInput()
{
	return bAttackInput;
}

bool ABaseEnemy::ConsumeAttackInput()
{
	bool bRetVal = bAttackInput;
	bAttackInput = false;
	return bRetVal;
}

void ABaseEnemy::ReceiveDamage(float IncomingDamage, EDamageType DamageType)
{
	Health -= IncomingDamage;
	if (Health <= 0)
	{
		GetTargetAsTank()->RecieveXp(GivenXp);
		EnemyDie(DamageType);
	}
}

void ABaseEnemy::EnemyDie_Implementation(EDamageType DamageType)
{
	Destroy();
}

bool ABaseEnemy::EnemyAIShouldAttack_Implementation()
{
	if (AActor* Target = GetTarget())
	{
		FVector OurLocation = GetActorLocation();
		
		float DistSqXY = FVector::DistSquaredXY(Target->GetActorLocation(), OurLocation);
		if (DistSqXY <= (AttackDistance * AttackDistance))
		{
			return true;
		}
	}
	return false;
}