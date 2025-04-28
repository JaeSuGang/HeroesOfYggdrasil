// Safe Timer Binding with Valid Checks

#include "Enemy/AI/BTTaskNode_Await.h"
#include "TimerManager.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UObject/WeakObjectPtr.h"

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
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);

	if (IsValid(PlayAIData.SelfAnimPawn))
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}

	if (EnemyCharacter->GetAttributeComponent()->HasTag(TEXT("Enemy.Debuff.Stunned"))) {
		ChangeState(_OwnerComp, EEnemyAIState::Idle);
		return;
	}
	
	if (EnemyCharacter->GetAttributeComponent()->HasTag(TEXT("Enemy.State.Hit")) && !EnemyCharacter->GetDataKey().StartsWith(TEXT("Dragon"))) {
		
		ChangeState(_OwnerComp, EEnemyAIState::Hit);
		return;
	}

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

	



	if (IsValid(EnemyCharacter))
	{
		FString DataKeyStr = EnemyCharacter->GetDataKey();
		TWeakObjectPtr<AEnemyCharacter> WeakEnemy = EnemyCharacter;
		TWeakObjectPtr<UBehaviorTreeComponent> WeakOwner = Cast<UBehaviorTreeComponent>(&_OwnerComp);

		float HeroDefense = TargetCharacter->GetAttributeComponent()->DefensePoints;

		double HeroDefenseRate = (HeroDefense / (HeroDefense + 100.f));
		float HeroDamageAmount = WeakEnemy->GetAttributeComponent()->AttackPoints;
		HeroDamageAmount *= (1.f - HeroDefenseRate);
		WeakEnemy->GetAttributeComponent()->AttackPoints = HeroDamageAmount;

		float Duration = FMath::Max(PlayAIData.Data.AwaitTime, 0.1f);
		FTimerDelegate TimerDel;
		FTimerHandle TimerHandle;

		if (EEnemyType::Dragon != EnemyCharacter->ConvertStringToEnemyType(DataKeyStr))
		{
			TimerDel.BindLambda([this, WeakOwner, WeakEnemy]() {
				if (!WeakOwner.IsValid() || !WeakEnemy.IsValid()) return;

				AEnemyCharacter* EnemyChar = WeakEnemy.Get();
				UBehaviorTreeComponent* Comp = Cast<UBehaviorTreeComponent>(WeakOwner.Get());

				if (!EnemyChar || !Comp) return;

				if (EnemyChar->GetAttributeComponent()->HasTag(TEXT("Enemy.Debuff.Stunned"))) {
					ChangeState(*Comp, EEnemyAIState::Idle);
					return;
				}

				if (EnemyChar->GetAttributeComponent()->HasTag(TEXT("Enemy.State.Hit")) && !EnemyChar->GetDataKey().StartsWith(TEXT("Dragon"))) {
					EnemyChar->ClearHitState();
					ChangeState(*Comp, EEnemyAIState::Hit);
					return;
				}
				if (Comp)
				{
					ChangeState(*Comp, EEnemyAIState::Attack);
				}
				});
		}
		else
		{
			TimerDel.BindLambda([this, WeakOwner, WeakEnemy]() {
				if (!WeakOwner.IsValid() || !WeakEnemy.IsValid()) return;

				AEnemyCharacter* EnemyChar = WeakEnemy.Get();
				UBehaviorTreeComponent* Comp = Cast<UBehaviorTreeComponent>(WeakOwner.Get());
				if (!EnemyChar || !Comp) return;

				float HealthPercent = EnemyChar->GetAttributeComponent()->GetHP() / EnemyChar->GetAttributeComponent()->MaxHP;
				FPlayAIData& LocaAIlData = UEnemyBTTaskNode::GetPlayAIData(*Comp);

				if (EnemyChar->GetAttributeComponent()->HasTag(TEXT("Enemy.Debuff.Stunned"))) {
					ChangeState(*Comp, EEnemyAIState::Idle);
					return;
				}

				if (HealthPercent <= 0.5f && !LocaAIlData.bUsedBreathAttack)
				{
					LocaAIlData.bUsedBreathAttack = true;
					ChangeState(*Comp, EEnemyAIState::DragonBreath);
				}
				else
				{
					FRandomStream RandStream;
					RandStream.GenerateNewSeed();
					float Rand = RandStream.FRand();

					if (Rand <= 0.6f)
					{
						ChangeState(*Comp, EEnemyAIState::Attack);
					}
					else
					{
						ChangeState(*Comp, EEnemyAIState::DragonMeteor);
					}
				}
				});
		}

		SelfActor->GetWorldTimerManager().SetTimer(
			TimerHandle,
			TimerDel,
			Duration,
			false
		);
	}
}

void UBTTaskNode_Await::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
	DeathCheck(_OwnerComp);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	APawn* SelfActor = _OwnerComp.GetAIOwner()->GetPawn();
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);

	if (!IsValid(EnemyCharacter)) return;

	if (EnemyCharacter->GetAttributeComponent()->HasTag(TEXT("Enemy.DeBuff.Stunned"))) // ✅ 스턴 상태면 무시
	{
		ChangeState(_OwnerComp, EEnemyAIState::Idle);
	}

	if (EnemyCharacter->GetAttributeComponent()->HasTag(TEXT("Enemy.State.Hit")) && !EnemyCharacter->GetDataKey().StartsWith(TEXT("Dragon"))) {
		
		ChangeState(_OwnerComp, EEnemyAIState::Hit);
		return;
	}

	if (IsValid(EnemyCharacter))
	{
		if (EEnemyType::Dragon != EnemyCharacter->ConvertStringToEnemyType(EnemyCharacter->GetDataKey()))
		{
			RotateToTargetActor(_OwnerComp, _DeltaSeconds);
		}
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