// Coded By AssortRock Unreal Engine Class Project

#include "Enemy/AI/BTTaskNode_Attack.h"
#include "Enemy/EnemyWarningRange.h"
#include "TimerManager.h"

UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	EnemyAIStateValue = EEnemyAIState::Attack;
}

void UBTTaskNode_Attack::Start(UBehaviorTreeComponent& _OwnerComp)
{
	Super::Start(_OwnerComp);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;
	
	if (IsValid(TargetActor))
	{
		TargetRangeLocation = TargetActor->GetActorLocation();
	}

	if (IsValid(SelfActor))
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}

	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);

	if (IsValid(EnemyCharacter))
	{
		FString DataKeyStr = EnemyCharacter->GetDataKey();

		if (DataKeyStr.StartsWith(TEXT("Minion_Archer")))
		{
			EnemyCharacter->RevealArrow();
		}
		else if (DataKeyStr.StartsWith(TEXT("Minion_Witch")))
		{
			EnemyCharacter->SpawnWarningRange(TargetActor);
		}
	}


	if (IsValid(TargetActor))
	{
		AYggCharacter* TargetCharacter = Cast<AYggCharacter>(TargetActor);
		if (!IsValid(TargetCharacter)) return;

		UCharacterAttributeComponent* TargetAttributecomponent = TargetCharacter->GetAttributeComponent();
		if (IsValid(TargetAttributecomponent) && TargetAttributecomponent->HasTag(TargetHeroDeath))
		{
			ChangeState(_OwnerComp, EEnemyAIState::TraceYggdrasil);
			return;
		}
	}


	// 타이머를 이용한 상태 전이 예약
	float Duration = FMath::Max(PlayAIData.Data.AttackTime, 0.1f);
	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;

	TimerDel.BindLambda([this, &_OwnerComp, EnemyCharacter]()
	{
		if (IsValid(EnemyCharacter))
		{
			FString DataKeyStr = EnemyCharacter->GetDataKey();

			if (DataKeyStr.StartsWith(TEXT("Minion_Archer")))
			{
				EnemyCharacter->SpawnAndFireArrow();
				EnemyCharacter->HideArrow();
			}
			else if (DataKeyStr.StartsWith(TEXT("Minion_Witch")))
			{
				EnemyCharacter->SpawnEnemySkillAttack(TargetRangeLocation);
			}
		}

		UEnemyBTTaskNode::ChangeState(_OwnerComp, EEnemyAIState::Await);
	});

	PlayAIData.SelfPawn->GetWorldTimerManager().SetTimer(
		TimerHandle,
		TimerDel,
		Duration,
		false
	);
}

void UBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	DeathCheck(_OwnerComp);
	RotateToTargetActor(_OwnerComp, _DeltaSeconds);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	APawn* SelfActor = PlayAIData.SelfPawn;
	AAIController* SelfController = SelfActor->GetController<AAIController>();

	if (SelfController)
	{
		SelfController->StopMovement();
	}
}

void UBTTaskNode_Attack::RotateToTargetActor(UBehaviorTreeComponent& _OwnerComp, float _DeltaSeconds)
{
	Super::RotateToTargetActor(_OwnerComp, _DeltaSeconds);
}

void UBTTaskNode_Attack::DeathCheck(UBehaviorTreeComponent& _OwnerComp)
{
	Super::DeathCheck(_OwnerComp);
}
