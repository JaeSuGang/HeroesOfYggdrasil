// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_Hit.h"

UBTTaskNode_Hit::UBTTaskNode_Hit()
{
	EnemyAIStateValue = EEnemyAIState::Hit;
}

void UBTTaskNode_Hit::Start(UBehaviorTreeComponent& _OwnerComp)
{
}

void UBTTaskNode_Hit::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
}
