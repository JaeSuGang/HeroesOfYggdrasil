// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Enemy/AI/EnemyBTTaskNode.h"
#include "BTTaskNode_Trace.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UBTTaskNode_Trace : public UEnemyBTTaskNode
{
	GENERATED_BODY()
public:

	UBTTaskNode_Trace();

	void Start(UBehaviorTreeComponent& _OwnerComp);

	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;
};
