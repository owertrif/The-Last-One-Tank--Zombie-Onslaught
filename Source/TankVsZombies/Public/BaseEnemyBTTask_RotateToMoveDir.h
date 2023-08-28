// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "BaseEnemyBTTask_RotateToMoveDir.generated.h"

/**
 * 
 */
UCLASS()
class TANKVSZOMBIES_API UBaseEnemyBTTask_RotateToMoveDir : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBaseEnemyBTTask_RotateToMoveDir();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
