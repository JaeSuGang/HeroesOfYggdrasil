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
	RotateToTargetActor(_OwnerComp, _DeltaSeconds);


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
	FVector TargetAxis = FVector{ (0.0, 0.0f, 1.0f) };

	if (RandomInt >= 5)
	{
		SelfActor->AddMovementInput(TargetDir.RotateAngleAxis(90.0f, TargetAxis));
	}
	else
	{
		SelfActor->AddMovementInput(TargetDir.RotateAngleAxis(-90.0f, TargetAxis));
	}
	
	
	Time -= _DeltaSeconds;

	// 공격 준비
	if (Time <= PlayAIData.Data.StandardZeroTime)
	{
		Time = PlayAIData.Data.StrafeTime;
		ChangeState(_OwnerComp, EEnemyAIState::ApproachToAttack);
		return;
	}

	// 복귀
	
	float Size = TargetDir.Size();
	if (Size >= PlayAIData.Data.TraceRange)
	{
		ChangeState(_OwnerComp, EEnemyAIState::TraceBack);
		return;
	}
}


void UBTTaskNode_Strafe::RotateToTargetActor(UBehaviorTreeComponent& _OwnerComp, float _DeltaSeconds)
{
	Super::RotateToTargetActor(_OwnerComp, _DeltaSeconds);
}
