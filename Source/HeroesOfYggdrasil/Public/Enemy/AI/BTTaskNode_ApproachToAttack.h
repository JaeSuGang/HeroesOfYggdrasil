// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Enemy/AI/EnemyBTTaskNode.h"
#include "BTTaskNode_ApproachToAttack.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UBTTaskNode_ApproachToAttack : public UEnemyBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTaskNode_ApproachToAttack();

	void Start(UBehaviorTreeComponent& _OwnerComp);

	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;
};
