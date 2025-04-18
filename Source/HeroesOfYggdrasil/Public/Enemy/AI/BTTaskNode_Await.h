// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Enemy/AI/EnemyBTTaskNode.h"
#include "BTTaskNode_Await.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UBTTaskNode_Await : public UEnemyBTTaskNode
{
	GENERATED_BODY()
public:
	UBTTaskNode_Await();

	void Start(UBehaviorTreeComponent& _OwnerComp);

	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;

	void RotateToTargetActor(UBehaviorTreeComponent& _OwnerComp, float _DeltaSeconds) override;

	virtual void DeathCheck(UBehaviorTreeComponent& _OwnerComp) override;

public:
};
