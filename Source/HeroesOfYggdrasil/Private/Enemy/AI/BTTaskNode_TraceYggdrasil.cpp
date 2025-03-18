// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_TraceYggdrasil.h"

UBTTaskNode_TraceYggdrasil::UBTTaskNode_TraceYggdrasil()
{
	EnemyAIStateValue = EEnemyAIState::TraceYggdrasil;
}

void UBTTaskNode_TraceYggdrasil::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}
}

void UBTTaskNode_TraceYggdrasil::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	// 일단 이그드라실 추적


	// 일정거리 안의 플레이어 발견


	// 플레이어한테 공격당했을 경우



}
