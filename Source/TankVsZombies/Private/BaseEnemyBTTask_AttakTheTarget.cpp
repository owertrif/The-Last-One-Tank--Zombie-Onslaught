// Fill out your copyright notice in the Description page of Project Settings.


#include "BaseEnemyBTTask_AttakTheTarget.h"
#include "BaseEnemy.h"
#include "Tank.h"
#include "Misc/App.h"

UBaseEnemyBTTask_AttakTheTarget::UBaseEnemyBTTask_AttakTheTarget()
{
}

EBTNodeResult::Type UBaseEnemyBTTask_AttakTheTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController{ OwnerComp.GetAIOwner() };
	APawn* AIPawn{ AIController->GetPawn() };

	if (ABaseEnemy* PossesedEnemy = Cast<ABaseEnemy>(AIPawn))
	{
		if (PossesedEnemy->EnemyAIShouldAttack() && PossesedEnemy->GetHealthRemaining() > 0)
		{
			float CurrentTime = GetWorld()->GetTimeSeconds();
			if (PossesedEnemy->GetAttackAvailibleTime() <= CurrentTime)
			{
				PossesedEnemy->SetAttackAvailibleTime(CurrentTime + PossesedEnemy->GetAttackCooldown());
				PossesedEnemy->EnemyAttack(FApp::GetDeltaTime(), PossesedEnemy->GetAttackCooldown());
				if (ATank* Target = PossesedEnemy->GetTargetAsTank())
				{
					Target->ReceiveDamage(PossesedEnemy->GetAttackDamage(), EDamageType::ZombieSplap);
				}
			}
		}
	}

	FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
	return EBTNodeResult::Succeeded;
}

