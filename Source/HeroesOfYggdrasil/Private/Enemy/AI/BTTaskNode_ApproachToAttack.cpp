// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_ApproachToAttack.h"

UBTTaskNode_ApproachToAttack::UBTTaskNode_ApproachToAttack()
{
	EnemyAIStateValue = EEnemyAIState::ApproachToAttack;
}

void UBTTaskNode_ApproachToAttack::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}
}

void UBTTaskNode_ApproachToAttack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
}
