// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_TraceBack.h"
#include "Enemy/EnemyCharacter.h"

UBTTaskNode_TraceBack::UBTTaskNode_TraceBack()
{
	EnemyAIStateValue = EEnemyAIState::TraceBack;
}

void UBTTaskNode_TraceBack::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}
}

void UBTTaskNode_TraceBack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	APawn* SelfActor = PlayAIData.SelfPawn;

	FVector TargetDir = PlayAIData.OriginPos - SelfActor->GetActorLocation();
	SelfActor->AddMovementInput(TargetDir);

	if (TargetDir.Size() < 100.0f)
	{
		PlayAIData.TargetActor = nullptr;
		ChangeState(_OwnerComp, EEnemyAIState::TraceYggdrasil);
		return;
	}
}
