// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_TraceBack.h"

UBTTaskNode_TraceBack::UBTTaskNode_TraceBack()
{
	EnemyAIStateValue = EEnemyAIState::TraceBack;
}

void UBTTaskNode_TraceBack::Start(UBehaviorTreeComponent& _OwnerComp)
{
}

void UBTTaskNode_TraceBack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
}
