// Coded By AssortRock Unreal Engine Class Project

#include "Enemy/AI/BTTaskNode_Await.h"
#include "TimerManager.h"

UBTTaskNode_Await::UBTTaskNode_Await()
{
	EnemyAIStateValue = EEnemyAIState::Await;
}

void UBTTaskNode_Await::Start(UBehaviorTreeComponent& _OwnerComp)
{
	Super::Start(_OwnerComp);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;
	AYggCharacter* TargetCharacter = Cast<AYggCharacter>(TargetActor);

	if (IsValid(PlayAIData.SelfAnimPawn))
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}


	// 거리 기반 상태 분기
	if (IsValid(TargetCharacter))
	{
		UCharacterAttributeComponent* TargetAttributeComponent = TargetCharacter->GetAttributeComponent();
		if (IsValid(TargetAttributeComponent) && TargetAttributeComponent->HasTag(TEXT("Character")))
		{
			FVector TargetDir = TargetActor->GetActorLocation() - SelfActor->GetActorLocation();
			float Distance = TargetDir.Size();

			if (Distance >= PlayAIData.Data.StrafeRange)
			{
				ChangeState(_OwnerComp, EEnemyAIState::Trace);
				return;
			}
			if (Distance >= PlayAIData.Data.AttackRange)
			{
				ChangeState(_OwnerComp, EEnemyAIState::ApproachToAttack);
				return;
			}
		}
	}


	// 공격 상태 전환
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);

	if (IsValid(EnemyCharacter))
	{
		FString DataKeyStr = EnemyCharacter->GetDataKey();

		if (EEnemyType::Dragon != EnemyCharacter->ConvertStringToEnemyType(DataKeyStr))
		{
			// 상태 전이 예약
			float Duration = FMath::Max(PlayAIData.Data.AwaitTime, 0.1f);
			FTimerDelegate TimerDel;
			FTimerHandle TimerHandle;

			TimerDel.BindLambda([this, &_OwnerComp]() {
				ChangeState(_OwnerComp, EEnemyAIState::Attack);
				});

			PlayAIData.SelfPawn->GetWorldTimerManager().SetTimer(
				TimerHandle,
				TimerDel,
				Duration,
				false
			);
		}
		else // 드래곤일 경우
		{
			float Duration = FMath::Max(PlayAIData.Data.AwaitTime, 0.1f);
			FTimerDelegate TimerDel;
			FTimerHandle TimerHandle;

			TimerDel.BindLambda([this, &_OwnerComp, EnemyCharacter]() {

				if (!IsValid(EnemyCharacter))
				{
					return;
				}

				float HealthPercent = EnemyCharacter->GetAttributeComponent()->GetHP() / EnemyCharacter->GetAttributeComponent()->MaxHP;
				// ex: 0.0 ~ 1.0
				FPlayAIData& LocalData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);


				if (HealthPercent <= 0.5f && !LocalData.bUsedBreathAttack)
				{
					LocalData.bUsedBreathAttack = true;
					ChangeState(_OwnerComp, EEnemyAIState::DragonBreath);
				}
				else
				{
					FRandomStream RandStream;
					RandStream.GenerateNewSeed();

					float Rand = RandStream.FRand(); // 0.0 ~ 1.0 float

					if (Rand <= 0.5f)
					{
						ChangeState(_OwnerComp, EEnemyAIState::Attack); // 일반 공격
					}
					else
					{
						ChangeState(_OwnerComp, EEnemyAIState::DragonMeteor); // 범위 공격
					}
				}
				});

			PlayAIData.SelfPawn->GetWorldTimerManager().SetTimer(
				TimerHandle,
				TimerDel,
				Duration,
				false
			);
		}

	}
	
	

}

void UBTTaskNode_Await::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	DeathCheck(_OwnerComp);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	APawn* SelfActor = _OwnerComp.GetAIOwner()->GetPawn();
	AActor* TargetActor = PlayAIData.TargetActor;
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);
	AYggCharacter* TargetCharacter = Cast<AYggCharacter>(TargetActor);

	if (IsValid(EnemyCharacter))
	{
		FString DataKeyStr = EnemyCharacter->GetDataKey();

		if (EEnemyType::Dragon != EnemyCharacter->ConvertStringToEnemyType(DataKeyStr))
		{
			RotateToTargetActor(_OwnerComp, _DeltaSeconds);
		}

	}
	if (IsValid(EnemyCharacter))
	{
		EnemyCharacter->GetMovementComponent()->StopMovementImmediately();
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
