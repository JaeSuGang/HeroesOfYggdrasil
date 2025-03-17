// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_Strafe.h"

UBTTaskNode_Strafe::UBTTaskNode_Strafe()
{
	EnemyAIStateValue = EEnemyAIState::Strafe;
}

void UBTTaskNode_Strafe::Start(UBehaviorTreeComponent& _OwnerComp)
{
	Random.Initialize(10);
	RandomInt = Random.RandRange(0, 9);
	Time = 0.0f;
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
		SelfActor->AddMovementInput((FVector::ForwardVector) * 50.0f * _DeltaSeconds);
	}
	else
	{
		SelfActor->AddMovementInput((FVector::BackwardVector) * 50.0f * _DeltaSeconds);
	}
	

	Time += _DeltaSeconds;

	// 공격 준비
	if (Time >= PlayAIData.Data.AttackTime)
	{
		ChangeState(_OwnerComp, EEnemyAIState::Attack);
		Time = 0.0f;
		return;
	}

	// 복귀
	FVector TargetDir = TargetActor->GetActorLocation() - SelfActor->GetActorLocation();
	float Size = TargetDir.Size();
	/*if (Size >= PlayAIData.Data.TraceRange)
	{
		ChangeState(_OwnerComp, EEnemyAIState::TraceBack);
		return;
	}*/
}
