// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Enemy/AI/EnemyBTTaskNode.h"
#include "BTTaskNode_DragonMeteor.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UBTTaskNode_DragonMeteor : public UEnemyBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTaskNode_DragonMeteor();

void Start(UBehaviorTreeComponent& _OwnerComp);

void TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds) override;

};
