// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_Death.h"

UBTTaskNode_Death::UBTTaskNode_Death()
{
	EnemyAIStateValue = EEnemyAIState::Death;
}

void UBTTaskNode_Death::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}
}

void UBTTaskNode_Death::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
}
