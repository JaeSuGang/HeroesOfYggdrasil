// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_Await.h"

UBTTaskNode_Await::UBTTaskNode_Await()
{
	EnemyAIStateValue = EEnemyAIState::Await;

}

void UBTTaskNode_Await::Start(UBehaviorTreeComponent& _OwnerComp)
{
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

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	AActor* TargetActor = PlayAIData.TargetActor;
	APawn* SelfActor = PlayAIData.SelfPawn;
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);

	AwaitTime -= _DeltaSeconds;
	
	if (EnemyCharacter != nullptr && AwaitTime <= PlayAIData.Data.RangeAttackTime)
	{
		FString DataKeyStr = EnemyCharacter->GetDataKey();
		
		// 저주술사인 경우
		if (FString("Minion_Witch") == DataKeyStr)
		{
			//EnemyCharacter->spawnrange();
			return;
		}
	}

	


	if (AwaitTime < PlayAIData.Data.StandardZeroTime)
	{
		ChangeState(_OwnerComp, EEnemyAIState::Attack);
		AwaitTime = PlayAIData.Data.AwaitTime;
	}


	FVector TargetDir = TargetActor->GetActorLocation() - SelfActor->GetActorLocation();
	float Size = TargetDir.Size();

	// 타겟이 플레이어인 경우
	if (FName("BP_YggHero") == PlayAIData.TargetActor->GetName().Left(10))
	{	
		// 플레이어가 공격범위를 벗어났을 때
		if (Size >= PlayAIData.Data.AttackRange)
		{
			ChangeState(_OwnerComp, EEnemyAIState::ApproachToAttack);
		}

		// 추적 범위를 넘어갔을 때
		if (Size >= PlayAIData.Data.StrafeRange)
		{
			ChangeState(_OwnerComp, EEnemyAIState::Trace);
			return;
		}
	}


}
