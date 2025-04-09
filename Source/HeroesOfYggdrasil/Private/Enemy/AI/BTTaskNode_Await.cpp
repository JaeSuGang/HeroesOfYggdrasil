// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_Await.h"

UBTTaskNode_Await::UBTTaskNode_Await()
{
	EnemyAIStateValue = EEnemyAIState::Await;

}

void UBTTaskNode_Await::Start(UBehaviorTreeComponent& _OwnerComp)
{
	Super::Start(_OwnerComp);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}

	AwaitTime = PlayAIData.Data.AwaitTime;

}

void UBTTaskNode_Await::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	DeathCheck(_OwnerComp);

	RotateToTargetActor(_OwnerComp, _DeltaSeconds);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	
	AActor* TargetActor = PlayAIData.TargetActor;
	AYggCharacter* TargetCharacter = Cast<AYggCharacter>(TargetActor);


	APawn* SelfActor = PlayAIData.SelfPawn;
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);
	
	EnemyCharacter->GetMovementComponent()->StopMovementImmediately();

	AwaitTime -= _DeltaSeconds;

	if (AwaitTime < PlayAIData.Data.StandardZeroTime)
	{
		ChangeState(_OwnerComp, EEnemyAIState::Attack);
		AwaitTime = PlayAIData.Data.AwaitTime;
		return;
	}


	FVector TargetDir = TargetActor->GetActorLocation() - SelfActor->GetActorLocation();
	float Size = TargetDir.Size();

	// 타겟이 플레이어인 경우

	if (IsValid(TargetCharacter))
	{
		UCharacterAttributeComponent* TargetAttributeComponent = TargetCharacter->GetAttributeComponent();
		if (IsValid(TargetAttributeComponent))
		{
			if (TargetAttributeComponent->HasTag(TEXT("Character")))
			{
				// 플레이어가 공격범위를 벗어났을 때
				if (Size >= PlayAIData.Data.AttackRange)
				{
					ChangeState(_OwnerComp, EEnemyAIState::ApproachToAttack);
					return;
				}

				// 추적 범위를 넘어갔을 때
				if (Size >= PlayAIData.Data.StrafeRange)
				{
					ChangeState(_OwnerComp, EEnemyAIState::Trace);
					return;
				}
			}
		}
	}
}

void UBTTaskNode_Await::RotateToTargetActor(UBehaviorTreeComponent& _OwnerComp, float _DeltaSeconds)
{
	Super::RotateToTargetActor(_OwnerComp, _DeltaSeconds);
}


void UBTTaskNode_Await::DeathCheck(UBehaviorTreeComponent& _OwnerComp)
{
	Super::DeathCheck(_OwnerComp);
}