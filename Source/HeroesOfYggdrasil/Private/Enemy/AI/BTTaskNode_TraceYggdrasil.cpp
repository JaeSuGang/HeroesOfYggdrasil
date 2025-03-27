// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_TraceYggdrasil.h"
#include "Enemy/EnemyAIController.h"

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

	CheckTime = PlayAIData.Data.StandardZeroTime;

}

void UBTTaskNode_TraceYggdrasil::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
	
	CheckTime -= _DeltaSeconds;

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	AActor* TargetActor = PlayAIData.TargetActor;
	
	APawn* SelfActor = PlayAIData.SelfPawn;
	FVector TargetDir = TargetActor->GetActorLocation() - SelfActor->GetActorLocation();
	AEnemyAIController* SelfController = SelfActor->GetController<AEnemyAIController>();

	
	
	

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
		PlayAIData.OriginPos = SelfActor->GetActorLocation();
		ChangeState(_OwnerComp, EEnemyAIState::Trace);
		return;
	}

	TargetDir.Z = 0.0f;
	float ReturnSize = TargetDir.Size() - 50.0f;

	// 공격준비
	if (ReturnSize <= PlayAIData.Data.YggAttackRange)
	{
		ChangeState(_OwnerComp, EEnemyAIState::Attack);
		return;
	}

	//SelfActor->AddMovementInput(TargetDir);

	if (SelfController != nullptr && TargetActor != nullptr && CheckTime < 0.0f)
	{

		SelfController->MoveToLocation(TargetActor->GetActorLocation(), PlayAIData.Data.YggAttackRange - 10.0f);
		CheckTime = PlayAIData.Data.TargetCheckTime;
	}
	

}
