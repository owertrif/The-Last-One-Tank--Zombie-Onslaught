// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyBTTasck_FindTarget.h"
#include "Kismet/GameplayStatics.h"
#include "Tank.h"
#include "BaseEnemy.h"

UBaseEnemyBTTasck_FindTarget::UBaseEnemyBTTasck_FindTarget()
{
	NodeName = TEXT("Find Target");
}

EBTNodeResult::Type UBaseEnemyBTTasck_FindTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	ATank* TargetPlayer;
	//Get AI pawn

	AAIController* AIController{ OwnerComp.GetAIOwner() };
	APawn* AIPawn {AIController->GetPawn()};

	//Get pawn origin
	const FVector Origin{ AIPawn->GetActorLocation() };

	//Obtain navigation system
	if (AActor* Target = UGameplayStatics::GetPlayerPawn(this, 0))
	{
		if (ABaseEnemy* PossesedEnemy = Cast<ABaseEnemy>(AIPawn))
		{
			PossesedEnemy->SetTarget(Target);
		}
		TargetPlayer = Cast<ATank>(Target);
		AIController->GetBlackboardComponent()->SetValueAsObject(BlackboardKey.SelectedKeyName, TargetPlayer);
	}

	FinishLatentTask( OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

FString UBaseEnemyBTTasck_FindTarget::GetStaticDescription() const
{
	return FString::Printf(TEXT("Target: %s"), *BlackboardKey.SelectedKeyName.ToString());
}
