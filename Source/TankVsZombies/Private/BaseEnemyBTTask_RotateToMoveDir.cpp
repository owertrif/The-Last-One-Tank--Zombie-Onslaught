// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyBTTask_RotateToMoveDir.h"
#include "Tank.h"
#include "BaseEnemy.h"

UBaseEnemyBTTask_RotateToMoveDir::UBaseEnemyBTTask_RotateToMoveDir()
{
	NodeName = TEXT("Face Right/Left depending at movement");
}

EBTNodeResult::Type UBaseEnemyBTTask_RotateToMoveDir::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	//Get AI pawn

	AAIController* AIController{ OwnerComp.GetAIOwner() };
	APawn* AIPawn{ AIController->GetPawn() };

	if (ABaseEnemy* AIEnemy = Cast<ABaseEnemy>(AIPawn))
	{
		if (AActor* TargetPlayer = AIEnemy->GetTarget())
		{
			//Calculating cos betwen target direction and enemy
			
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}
