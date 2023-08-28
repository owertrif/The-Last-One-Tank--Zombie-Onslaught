// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Tasks/BTTask_BlackboardBase.h"
#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "NavigationSystem.h"
#include "BaseEnemyBTTasck_FindTarget.generated.h"

/**
 * BTTask for finding target on a NavMesh
 */
UCLASS()
class TANKVSZOMBIES_API UBaseEnemyBTTasck_FindTarget : public UBTTask_BlackboardBase
{
	GENERATED_BODY()
public:
	UBaseEnemyBTTasck_FindTarget();

protected:
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	virtual FString GetStaticDescription() const override;
};
