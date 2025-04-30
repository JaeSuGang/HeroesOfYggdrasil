// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_Hit.h"
#include "GameFramework/Actor.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/SkeletalMeshComponent.h"

UBTTaskNode_Hit::UBTTaskNode_Hit()
{
	EnemyAIStateValue = EEnemyAIState::Hit;
}

void UBTTaskNode_Hit::Start(UBehaviorTreeComponent& _OwnerComp)
{
	Super::Start(_OwnerComp);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	APawn* OwningPawn = _OwnerComp.GetAIOwner()->GetPawn();
	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwningPawn);

	if (!IsValid(SelfActor)) return;
	
	AEnemyAIController* SelfController = SelfActor->GetController<AEnemyAIController>();

	TargetCheck(_OwnerComp);

	if (IsValid(PlayAIData.SelfAnimPawn))
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}

	const float KnockBackDistance = 100.0f; 

	if (!IsValid(SelfActor) || !IsValid(TargetActor)) return;

	FVector KnockBackDirection = (SelfActor->GetActorLocation() - TargetActor->GetActorLocation());
	KnockBackDirection.Z = 0.0f;
	KnockBackDirection.Normalize();

	FVector KnockBackLocation = SelfActor->GetActorLocation() + KnockBackDirection * KnockBackDistance;

	if (IsValid(Enemy))
	{
		Enemy->GetMovementComponent()->StopMovementImmediately();
		SelfController->MoveToLocation(KnockBackLocation);
	}


	if (Enemy->GetAttributeComponent()->HasTag(TEXT("Enemy.State.Hit")) && IsValid(Enemy))
	{
		
		float Duration = FMath::Max(0.3f, 0.1f);
		FTimerDelegate TimerDel;
		FTimerHandle TimerHandle;
		
		Enemy->HitPlaySound();

		TWeakObjectPtr<AEnemyCharacter> WeakEnemy = Enemy;
		FWeakObjectPtr WeakOwner = &_OwnerComp;

		TimerDel.BindLambda([this, WeakOwner, WeakEnemy]() {
			if (!WeakOwner.IsValid() || !WeakEnemy.IsValid()) return;

			AEnemyCharacter* EnemyChar = WeakEnemy.Get();
			UBehaviorTreeComponent* Comp = Cast<UBehaviorTreeComponent>(WeakOwner.Get());

			if (!EnemyChar || !Comp) return;

			ChangeState(*Comp, EEnemyAIState::Idle);
			});

		PlayAIData.SelfPawn->GetWorldTimerManager().SetTimer(
			TimerHandle,
			TimerDel,
			Duration,
			false
		);
	}
	


}

void UBTTaskNode_Hit::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	DeathCheck(_OwnerComp);

	RotateToTargetActor(_OwnerComp, _DeltaSeconds);
}


void UBTTaskNode_Hit::DeathCheck(UBehaviorTreeComponent& _OwnerComp)
{
	Super::DeathCheck(_OwnerComp);
}