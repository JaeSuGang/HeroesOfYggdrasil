// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Enemy/AI/EnemyBTTaskNode.h"
#include "BTTaskNode_Attack.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UBTTaskNode_Attack : public UEnemyBTTaskNode
{
	GENERATED_BODY()

public:

	UBTTaskNode_Attack();

	void Start(UBehaviorTreeComponent& _OwnerComp);

	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;

	void RotateToTargetActor(UBehaviorTreeComponent& _OwnerComp, float _DeltaSeconds) override;
public:
	UPROPERTY(EditAnywhere)
	double AttackTime;
};
