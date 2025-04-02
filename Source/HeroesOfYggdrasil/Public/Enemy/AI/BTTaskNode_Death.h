// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Enemy/AI/EnemyBTTaskNode.h"
#include "BTTaskNode_Death.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UBTTaskNode_Death : public UEnemyBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTaskNode_Death();

	void Start(UBehaviorTreeComponent& _OwnerComp);

	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;

private:

	float DeathTime;
};
