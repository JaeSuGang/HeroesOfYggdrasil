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

	// 시작할 때 타겟 이그드라실 세팅
	YggdrasilCheck(_OwnerComp);
}

void UBTTaskNode_TraceYggdrasil::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	AActor* TargetActor = PlayAIData.TargetActor;

	// 이동 중 플레이어 타겟 체크
	TargetCheck(_OwnerComp);
	


	// 이그드라실 null(죽음)
	if (nullptr == TargetActor)
	{
		ChangeState(_OwnerComp, EEnemyAIState::Idle);
		return;
	}

	// 감지 범위 안에 플레이어 들어오면 플레이어 추적
	if (FName("BP_YggHero") == PlayAIData.TargetActor->GetName().Left(10))
	{
		ChangeState(_OwnerComp, EEnemyAIState::Trace);
		return;
	}

	APawn* SelfActor = PlayAIData.SelfPawn;
	FVector TargetDir = TargetActor->GetActorLocation() - SelfActor->GetActorLocation();

	// 공격준비
	if (TargetDir.Size() <= PlayAIData.Data.AttackRange)
	{
		ChangeState(_OwnerComp, EEnemyAIState::Strafe);
		return;
	}

	SelfActor->AddMovementInput(TargetDir);

	// 일단 이그드라실 추적


	// 일정거리 안의 플레이어 발견


	// 플레이어한테 공격당했을 경우



}
