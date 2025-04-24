// Safe Timer Binding with Valid Checks

#include "Enemy/AI/BTTaskNode_Attack.h"
#include "Enemy/EnemyWarningRange.h"
#include "TimerManager.h"
#include "UObject/WeakObjectPtr.h"

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
		RotateToTargetActor(_OwnerComp, 0.1f);
	}

	if (IsValid(EnemyCharacter))
	{
		FString DataKeyStr = EnemyCharacter->GetDataKey();
		EEnemyType EnemyType = EnemyCharacter->ConvertStringToEnemyType(DataKeyStr);
		if (EnemyType == EEnemyType::Minion_Archer)
		{
			EnemyCharacter->RevealArrow();
		}
		else if (EnemyType == EEnemyType::Minion_Witch)
		{
			EnemyCharacter->SpawnWarningRange(TargetActor);
		}
	}

	if (EnemyCharacter->GetAttributeComponent()->HasTag(TEXT("Enemy.Debuff.Stunned"))) {
		ChangeState(_OwnerComp, EEnemyAIState::Idle);
		return;
	}

	if (EnemyCharacter->GetAttributeComponent()->HasTag(TEXT("Enemy.State.Hit"))) {
		EnemyCharacter->ClearHitState();
		ChangeState(_OwnerComp, EEnemyAIState::Hit);
		return;
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

	float Duration = FMath::Max(PlayAIData.Data.AttackTime, 0.1f);
	FTimerDelegate TimerDel;
	FTimerHandle TimerHandle;

	TWeakObjectPtr<AEnemyCharacter> WeakEnemy = EnemyCharacter;
	FWeakObjectPtr WeakOwner = &_OwnerComp;
	FVector StoredTargetLocation = TargetRangeLocation;

	TimerDel.BindLambda([this, WeakOwner, WeakEnemy, StoredTargetLocation, TargetActor]() {
		if (!WeakOwner.IsValid() || !WeakEnemy.IsValid()) return;

		AEnemyCharacter* EnemyChar = WeakEnemy.Get();
		UBehaviorTreeComponent* Comp = Cast<UBehaviorTreeComponent>(WeakOwner.Get());

		if (!EnemyChar || !Comp) return;

		FString DataKeyStr = EnemyChar->GetDataKey();
		EEnemyType Type = EnemyChar->ConvertStringToEnemyType(DataKeyStr);

		if (EnemyChar->GetAttributeComponent()->HasTag(TEXT("Enemy.Debuff.Stunned"))) {
			ChangeState(*Comp, EEnemyAIState::Idle);
			return;
		}

		if (EnemyChar->GetAttributeComponent()->HasTag(TEXT("Enemy.State.Hit"))) {
			EnemyChar->ClearHitState();
			ChangeState(*Comp, EEnemyAIState::Hit);
			return;
		}

		if (Type == EEnemyType::Minion_Archer)
		{
			EnemyChar->SpawnAndFireArrow(TargetActor);
			EnemyChar->HideArrow();
		}
		else if (Type == EEnemyType::Minion_Witch)
		{
			EnemyChar->SpawnEnemySkillAttack(StoredTargetLocation, TargetActor);
		}

		ChangeState(*Comp, EEnemyAIState::Await);
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

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	APawn* SelfActor = PlayAIData.SelfPawn;
	AAIController* SelfController = SelfActor->GetController<AAIController>();
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);


	if (!IsValid(EnemyCharacter)) return;

	if (EnemyCharacter->GetAttributeComponent()->HasTag(TEXT("Enemy.DeBuff.Stunned"))) // ✅ 스턴 상태면 무시
	{
		ChangeState(_OwnerComp, EEnemyAIState::Idle);
	}

	if (EnemyCharacter->GetAttributeComponent()->HasTag(TEXT("Enemy.State.Hit"))) {
		EnemyCharacter->ClearHitState();
		ChangeState(_OwnerComp, EEnemyAIState::Hit);
		return;
	}

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