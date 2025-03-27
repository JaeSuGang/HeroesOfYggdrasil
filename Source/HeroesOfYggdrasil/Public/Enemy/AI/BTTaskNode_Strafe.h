// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "Enemy/AI/EnemyBTTaskNode.h"
#include "BTTaskNode_Strafe.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UBTTaskNode_Strafe : public UEnemyBTTaskNode
{
	GENERATED_BODY()
	
public:

	UBTTaskNode_Strafe();

	void Start(UBehaviorTreeComponent& _OwnerComp);

	void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;

	void RotateToTargetActor(UBehaviorTreeComponent& _OwnerComp, float _DeltaSeconds) override;

private:
	UPROPERTY(EditAnywhere)
	FRandomStream Random;
	UPROPERTY(EditAnywhere)
	int32 RandomInt;
	UPROPERTY(EditAnywhere)
	double Time;
	
};
