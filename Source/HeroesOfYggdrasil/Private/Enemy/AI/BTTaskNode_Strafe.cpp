// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_Strafe.h"
#include "Data/YggStructData.h"

UBTTaskNode_Strafe::UBTTaskNode_Strafe()
{
	EnemyAIStateValue = EEnemyAIState::Strafe;
}

void UBTTaskNode_Strafe::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}

	Random.Initialize(FMath::RandRange(0, 10000));
	RandomInt = Random.RandRange(0, 9);
	Time = PlayAIData.Data.StrafeTime;
}

void UBTTaskNode_Strafe::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
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

	if (RandomInt >= 5)
	{
		SelfActor->AddMovementInput((FVector::ForwardVector) * PlayAIData.Data.StrafeSpeed * _DeltaSeconds);
	}
	else
	{
		SelfActor->AddMovementInput((FVector::BackwardVector) * PlayAIData.Data.StrafeSpeed * _DeltaSeconds);
	}
	
	
	Time -= _DeltaSeconds;

	// 공격 준비
	if (Time <= 0.0f)
	{
		Time = PlayAIData.Data.StrafeTime;
		ChangeState(_OwnerComp, EEnemyAIState::ApproachToAttack);
		return;
	}

	// 복귀
	FVector TargetDir = TargetActor->GetActorLocation() - SelfActor->GetActorLocation();
	float Size = TargetDir.Size();
	if (Size >= PlayAIData.Data.TraceRange)
	{
		ChangeState(_OwnerComp, EEnemyAIState::TraceBack);
		return;
	}
}
