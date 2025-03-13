// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/EnemyBTTaskNode.h"
#include "BehaviorTree/BTTaskNode.h"
#include <Kismet/GameplayStatics.h>
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
	FPlayAIData& PlayAIData = GetPlayAIData(_OwnerComp);
	PlayAIData.EnemyAIState = _State;
	FinishLatentTask(_OwnerComp, EBTNodeResult::Failed);
}

FPlayAIData& UEnemyBTTaskNode::GetPlayAIData(UBehaviorTreeComponent& _OwnerComp)
{
	UObject* AIData = _OwnerComp.GetBlackboardComponent()->GetValueAsObject(UEnemyConst::AI::EnemyAIDataName);
	return Cast<UAIDataObject>(AIData)->PlayData;
}

void UEnemyBTTaskNode::TargetCheck(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = GetPlayAIData(_OwnerComp);

	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;

	if (nullptr == TargetActor)
	{
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsWithTag(GetWorld(), PlayAIData.Data.TargetGroupName, OutActors);

		AActor* CheckActor = nullptr;
		float CurTargetDistance = TNumericLimits<float>::Max();
		for (size_t i = 0; i < OutActors.Num(); i++)
		{
			CheckActor = OutActors[i];
			float TargetDis = (SelfActor->GetActorLocation() - CheckActor->GetActorLocation()).Size();
			if (TargetDis < PlayAIData.Data.TraceRange && TargetDis < CurTargetDistance)
			{
				TargetActor = CheckActor;
			}
		}

		if (nullptr != TargetActor)
		{
			PlayAIData.TargetActor = TargetActor;
		}
	}
}

