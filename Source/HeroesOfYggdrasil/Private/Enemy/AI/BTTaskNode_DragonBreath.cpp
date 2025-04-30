// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_DragonBreath.h"

UBTTaskNode_DragonBreath::UBTTaskNode_DragonBreath()
{
	EnemyAIStateValue = EEnemyAIState::DragonBreath;
}

void UBTTaskNode_DragonBreath::Start(UBehaviorTreeComponent& _OwnerComp)
{
	Super::Start(_OwnerComp);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;

	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);

	if (!IsValid(SelfActor)) return;
	
	AAIController* SelfController = SelfActor->GetController<AAIController>();

	

	// 이동 중지
	if (IsValid(SelfController))
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

		EnemyCharacter->DragonBreathPlaySound();
		EnemyCharacter->DragonBreath();

	}

	// 애니메이션 상태 전환
	if (IsValid(SelfActor))
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}

	float Duration = FMath::Max(9.f, 0.1f);
	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;

	TimerDel.BindLambda([this, &_OwnerComp, EnemyCharacter]()
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

void UBTTaskNode_DragonBreath::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
}
