// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BaseEnemyBTTask_AttakTheTarget.generated.h"

class ABaseEnemy;
/**
 * 
 */
UCLASS()
class TANKVSZOMBIES_API UBaseEnemyBTTask_AttakTheTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBaseEnemyBTTask_AttakTheTarget();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
