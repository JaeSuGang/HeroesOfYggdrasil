// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_Idle.h"
#include "Enemy/AI/EnemyBTTaskNode.h"
#include "Data/YggStructData.h"
#include "Data/YggEnumData.h"

UBTTaskNode_Idle::UBTTaskNode_Idle()
{
	EnemyAIStateValue = EEnemyAIState::Idle;
	bNotifyTick = true;
}

void UBTTaskNode_Idle::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		//PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}
}

void UBTTaskNode_Idle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	FPlayAIData& AIData = GetPlayAIData(_OwnerComp);
	/*if (AIData.CurPatrolTime > AIData.Data.MaxPatrolTime)
	{
		ChangeState(_OwnerComp, EEnemyAIState::Trace);
		return;
	}*/

	TargetCheck(_OwnerComp);

	if (nullptr != AIData.TargetActor)
	{
		ChangeState(_OwnerComp, EEnemyAIState::Trace);
		return;
	}
}