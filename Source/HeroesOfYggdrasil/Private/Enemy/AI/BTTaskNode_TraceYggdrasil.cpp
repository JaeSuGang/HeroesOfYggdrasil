// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_TraceYggdrasil.h"

UBTTaskNode_TraceYggdrasil::UBTTaskNode_TraceYggdrasil()
{
	EnemyAIStateValue = EEnemyAIState::TraceYggdrasil;
}

void UBTTaskNode_TraceYggdrasil::Start(UBehaviorTreeComponent& _OwnerComp)
{
}

void UBTTaskNode_TraceYggdrasil::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
}
