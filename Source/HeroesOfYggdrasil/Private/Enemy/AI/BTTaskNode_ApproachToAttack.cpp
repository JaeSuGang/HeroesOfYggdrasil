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
	
	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	AActor* TargetActor = PlayAIData.TargetActor;

	// 타겟 null(죽음)
	if (nullptr == TargetActor)
	{
		ChangeState(_OwnerComp, EEnemyAIState::TraceBack);
		return;
	}

	APawn* SelfActor = PlayAIData.SelfPawn;
	FVector TargetDir = TargetActor->GetActorLocation() - SelfActor->GetActorLocation();

	SelfActor->AddMovementInput(TargetDir);

	if (TargetDir.Size() <= PlayAIData.Data.AttackRange)
	{
		ChangeState(_OwnerComp, EEnemyAIState::Attack);
		return;
	}

	float Size = TargetDir.Size();
	if (Size >= PlayAIData.Data.TraceRange)
	{
		ChangeState(_OwnerComp, EEnemyAIState::TraceBack);
		return;
	}
}
