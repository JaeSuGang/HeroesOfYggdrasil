// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/EnemyBTTaskNode.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BehaviorTree/BlackboardComponent.h"



UEnemyBTTaskNode::UEnemyBTTaskNode()
{
	bNotifyTick = true;
}

void UEnemyBTTaskNode::Start(UBehaviorTreeComponent& _OwnerComp)
{
}

EBTNodeResult::Type UEnemyBTTaskNode::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	Start(_OwnerComp);

	if (PlayAIData.EnemyAIState != EnemyAIStateValue)
	{
		return EBTNodeResult::Type::Failed;
	}

	return EBTNodeResult::Type::InProgress;
}

void UEnemyBTTaskNode::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

}

void UEnemyBTTaskNode::ChangeState(UBehaviorTreeComponent& _OwnerComp, EEnemyAIState _State)
{

}

FPlayAIData& UEnemyBTTaskNode::GetPlayAIData(UBehaviorTreeComponent& _OwnerComp)
{
	UObject* Data = _OwnerComp.GetBlackboardComponent()->GetValueAsObject(UEnemyConst::AI::EnemyAIDataName);
	return Cast<UAIDataObject>(Data)->PlayData;
}

