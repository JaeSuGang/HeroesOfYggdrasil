// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_DeathFallen.h"

UBTTaskNode_DeathFallen::UBTTaskNode_DeathFallen()
{
	EnemyAIStateValue = EEnemyAIState::DeathFallen;
}

void UBTTaskNode_DeathFallen::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}
}

void UBTTaskNode_DeathFallen::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
}
