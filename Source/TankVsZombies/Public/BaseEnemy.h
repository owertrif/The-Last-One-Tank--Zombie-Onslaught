// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "UDamageInterface.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BaseEnemy.generated.h"

class ATank;

UCLASS()
class TANKVSZOMBIES_API ABaseEnemy : public ACharacter, public IDamageInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABaseEnemy();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable, Category = "BaseEnemy")
		void SetTarget(AActor* NewTarget);

	UFUNCTION(BlueprintNativeEvent, Category = "AI")
		bool EnemyAIShouldAttack();
		virtual bool EnemyAIShouldAttack_Implementation();

	UFUNCTION(BlueprintCallable, Category = "BaseEnemy")
		AActor* GetTarget();
	UFUNCTION(BlueprintCallable, Category = "BaseEnemy")
		ATank* GetTargetAsTank();

	UFUNCTION(BlueprintCallable, Category = "BaseEnemy")
		float GetAttackDistance();
	UFUNCTION(BlueprintCallable, Category = "BaseEnemy")
		float GetAttackDamage() { return AttackDamage; }
	UFUNCTION(BlueprintCallable, Category = "BaseEnemy")
		float GetAttackAvailibleTime() { return AttackAvailibleTime; }
	UFUNCTION(BlueprintCallable, Category = "BaseEnemy")
		float GetAttackCooldown() { return AttackCooldown; }

	UFUNCTION(BlueprintCallable, Category = "BaseEnemy")
		void SetAttackAvailibleTime(float Time) { AttackAvailibleTime = Time; }

	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
		void EnemyWalk(float DeltaSeconds, float DistanceWalked);
	UFUNCTION(BlueprintImplementableEvent, Category = "AI")
		void EnemyAttack(float DeltaSeconds, float AtkCooldown);
	UFUNCTION(BlueprintNativeEvent, Category = "AI")
		void EnemyDie(EDamageType DamageType);

	UFUNCTION(BlueprintCallable, Category = "Pawn|Input", meta = (Keywords = "AddInput"))
		virtual void AddRotationInput(float DeltaYawDegrees);
	UFUNCTION(BlueprintCallable, Category = "Pawn|Input", meta = (Keywords = "ConsumeInput"))
		virtual float GetRotationInput();
	UFUNCTION(BlueprintCallable, Category = "Pawn|Input", meta = (Keywords = "ConsumeInput"))
		virtual float ConsumeRotationInput();
	UFUNCTION(BlueprintCallable, Category = "Pawn|Input", meta = (Keywords = "AddInput"))
		virtual void AddAttackInput();
	UFUNCTION(BlueprintCallable, Category = "Pawn|Input", meta = (Keywords = "ConsumeInput"))
		virtual bool GetAttackInput();
	UFUNCTION(BlueprintCallable, Category = "Pawn|Input", meta = (Keywords = "ConsumeInput"))
		virtual bool ConsumeAttackInput();


	//Damage interface
	virtual void ReceiveDamage(float IncomingDamage, EDamageType DamageType) override;
	virtual float GetHealthRemaining()override { return Health; };

private:

	UPROPERTY(VisibleInstanceOnly, Category = "AI")
		AActor* TargetActor;

	UPROPERTY(VisibleInstanceOnly, Category = "AI")
		ATank* TargetTank;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseEnenmy", meta = (ClampMin = "0.0"))
		float Health;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseEnenmy", meta = (ClampMin = "0.0"))
		float AttackDamage;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseEnenmy", meta = (ClampMin = "0.0"))
		float GivenXp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseEnenmy", meta = (ClampMin = "0.0"))
		float AttackDistance;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseEnenmy", meta = (ClampMin = "0.0"))
		float AttackCooldown;
	UPROPERTY(Transient, VisibleInstanceOnly, BlueprintReadWrite, Category = "BaseEnenmy")
		float AttackAvailibleTime;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "BaseEnenmy")
		FName EnemyCollisionProfile;

private:
	float YawInput;

	int32 bAttackInput : 1;

};
