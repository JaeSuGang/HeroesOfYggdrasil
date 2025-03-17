// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_Attack.h"

UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	EnemyAIStateValue = EEnemyAIState::Attack;
}

void UBTTaskNode_Attack::Start(UBehaviorTreeComponent& _OwnerComp)
{
}

void UBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
}
