// Coded By AssortRock Unreal Engine Class Project

#include "Enemy/AI/BTTaskNode_Attack.h"
#include "Enemy/EnemyWarningRange.h"
#include "TimerManager.h"

UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	// 기본 상태를 Attack으로 설정
	EnemyAIStateValue = EEnemyAIState::Attack;
}

void UBTTaskNode_Attack::Start(UBehaviorTreeComponent& _OwnerComp)
{
	Super::Start(_OwnerComp);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;

	// 타겟의 위치 저장
	if (IsValid(TargetActor))
	{
		TargetRangeLocation = TargetActor->GetActorLocation();
	}

	// 애니메이션 상태 전환
	if (IsValid(SelfActor))
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}

	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);

	if (IsValid(EnemyCharacter))
	{
		FString DataKeyStr = EnemyCharacter->GetDataKey();

		// 타입에 따라 다른 동작 수행
		if (EEnemyType::Minion_Archer == EnemyCharacter->ConvertStringToEnemyType(DataKeyStr))
		{
			EnemyCharacter->RevealArrow();
		}
		else if (EEnemyType::Minion_Witch == EnemyCharacter->ConvertStringToEnemyType(DataKeyStr))
		{
			EnemyCharacter->SpawnWarningRange(TargetActor);
		}
		else if (EEnemyType::Dragon == EnemyCharacter->ConvertStringToEnemyType(DataKeyStr))
		{
			RotateToTargetActor(_OwnerComp, 0.01f);
			//EnemyCharacter->DragonRangeAttack(TargetActor);
			EnemyCharacter->DragonBreath();
		}
	}

	// 타겟이 사망 상태이면 상태 전환
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

	// 공격 완료 후 상태 전이를 위한 타이머 설정
	float Duration = FMath::Max(PlayAIData.Data.AttackTime, 0.1f);
	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;

	TimerDel.BindLambda([this, &_OwnerComp, EnemyCharacter]()
		{
			if (IsValid(EnemyCharacter))
			{
				FString DataKeyStr = EnemyCharacter->GetDataKey();
				
				// 공격 애니메이션/이펙트 수행
				if (EEnemyType::Minion_Archer == EnemyCharacter->ConvertStringToEnemyType(DataKeyStr))
				{
					EnemyCharacter->SpawnAndFireArrow();
					EnemyCharacter->HideArrow();
				}
				else if (EEnemyType::Minion_Witch == EnemyCharacter->ConvertStringToEnemyType(DataKeyStr))
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

	// 사망 체크
	DeathCheck(_OwnerComp);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	APawn* SelfActor = PlayAIData.SelfPawn;
	AAIController* SelfController = SelfActor->GetController<AAIController>();
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);

	if (IsValid(EnemyCharacter))
	{
		FString DataKeyStr = EnemyCharacter->GetDataKey();

		// 드래곤 외 몬스터는 타겟 방향으로 회전
		if (EEnemyType::Dragon != EnemyCharacter->ConvertStringToEnemyType(DataKeyStr))
		{
			RotateToTargetActor(_OwnerComp, _DeltaSeconds);
		}
	}

	// 이동 중지
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
