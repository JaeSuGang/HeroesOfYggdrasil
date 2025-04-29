// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_Idle.h"
#include "Enemy/AI/EnemyBTTaskNode.h"
#include "Data/YggStructData.h"
#include "Data/YggEnumData.h"

UBTTaskNode_Idle::UBTTaskNode_Idle()
{
	EnemyAIStateValue = EEnemyAIState::Idle;
	bNotifyTick = true;
}

void UBTTaskNode_Idle::Start(UBehaviorTreeComponent& _OwnerComp)
{
	Super::Start(_OwnerComp);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	APawn* OwningPawn = _OwnerComp.GetAIOwner()->GetPawn();
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwningPawn);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}

	if (Enemy->GetAttributeComponent()->HasTag(TEXT("Enemy.State.Hit")))
	{

		float Duration = FMath::Max(0.5f, 0.1f);
		FTimerDelegate TimerDel;
		FTimerHandle TimerHandle;

		TWeakObjectPtr<AEnemyCharacter> WeakEnemy = Enemy;
		FWeakObjectPtr WeakOwner = &_OwnerComp;

		TimerDel.BindLambda([this, WeakOwner, WeakEnemy]() {
			if (!WeakOwner.IsValid() || !WeakEnemy.IsValid()) return;

			AEnemyCharacter* EnemyChar = WeakEnemy.Get();
			UBehaviorTreeComponent* Comp = Cast<UBehaviorTreeComponent>(WeakOwner.Get());

			if (!EnemyChar || !Comp) return;

			WeakEnemy->ClearHitState();
			ChangeState(*Comp, EEnemyAIState::TraceYggdrasil);
			});

		PlayAIData.SelfPawn->GetWorldTimerManager().SetTimer(
			TimerHandle,
			TimerDel,
			Duration,
			false
		);
	}

}

void UBTTaskNode_Idle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	DeathCheck(_OwnerComp);

	RotateToTargetActor(_OwnerComp, _DeltaSeconds);

	FPlayAIData& AIData = GetPlayAIData(_OwnerComp);
	APawn* OwningPawn = _OwnerComp.GetAIOwner()->GetPawn();
	AYggCharacter* Enemy = Cast<AYggCharacter>(OwningPawn);

	APawn* SelfActor = AIData.SelfPawn;
	AAIController* SelfController = SelfActor->GetController<AAIController>();
	AActor* TargetActor = AIData.TargetActor;

	if (IsValid(TargetActor))
	{
		if (TargetActor->GetName().StartsWith(TEXT("BP_Yggdrasil")))
		{
			AYggCharacter* Yggdrasil = Cast<AYggCharacter>(TargetActor);
			if (IsValid(Yggdrasil))
			{
				UCharacterAttributeComponent* YggdarsilAttri = Yggdrasil->GetAttributeComponent();
				if (IsValid(YggdarsilAttri))
				{
					if (YggdarsilAttri->GetHP() < 0.0f)
					{
						return;
					}
				}
			}
		}
	}



	if (!Enemy->GetAttributeComponent()->HasTag("Enemy.DeBuff.Stunned") && !Enemy->GetAttributeComponent()->HasTag("Enemy.State.Hit"))
	{
		ChangeState(_OwnerComp, EEnemyAIState::TraceYggdrasil);
	}



	if (SelfController)
	{
		SelfController->StopMovement();
	}

	TargetCheck(_OwnerComp);
}


void UBTTaskNode_Idle::DeathCheck(UBehaviorTreeComponent& _OwnerComp)
{
	Super::DeathCheck(_OwnerComp);
}
