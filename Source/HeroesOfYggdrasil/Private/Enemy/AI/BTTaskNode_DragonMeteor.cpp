// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_DragonMeteor.h"

UBTTaskNode_DragonMeteor::UBTTaskNode_DragonMeteor()
{
	EnemyAIStateValue = EEnemyAIState::DragonMeteor;
}

void UBTTaskNode_DragonMeteor::Start(UBehaviorTreeComponent& _OwnerComp)
{
	Super::Start(_OwnerComp);
	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;

	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);
	
	AAIController* SelfController = SelfActor->GetController<AAIController>();
	// 이동 중지
	if (SelfController)
	{
		SelfController->StopMovement();
	}

	if (IsValid(EnemyCharacter))
	{
		FString DataKeyStr = EnemyCharacter->GetDataKey();
		if (EEnemyType::Dragon != EnemyCharacter->ConvertStringToEnemyType(DataKeyStr))
		{
			ChangeState(_OwnerComp, EEnemyAIState::TraceYggdrasil);
			return;
		}

		EnemyCharacter->DragonRangeAttack(TargetActor);
	}

	// 애니메이션 상태 전환
	if (IsValid(SelfActor))
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}

	float Duration = FMath::Max(2.8f, 0.1f);
	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;

	TimerDel.BindLambda([this, &_OwnerComp]()
		{
			UEnemyBTTaskNode::ChangeState(_OwnerComp, EEnemyAIState::Await);
		});

	PlayAIData.SelfPawn->GetWorldTimerManager().SetTimer(
		TimerHandle,
		TimerDel,
		Duration,
		false
	);

}

void UBTTaskNode_DragonMeteor::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
}
