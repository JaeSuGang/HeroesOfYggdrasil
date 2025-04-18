// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Enemy/AI/EnemyBTTaskNode.h"
#include "BTTaskNode_DragonBreath.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UBTTaskNode_DragonBreath : public UEnemyBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_DragonBreath();

	void Start(UBehaviorTreeComponent& _OwnerComp);

	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;

	
};
