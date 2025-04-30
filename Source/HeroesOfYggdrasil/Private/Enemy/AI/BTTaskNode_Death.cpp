// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_Death.h"
#include "Components/CapsuleComponent.h"

UBTTaskNode_Death::UBTTaskNode_Death()
{
	EnemyAIStateValue = EEnemyAIState::Death;
}

void UBTTaskNode_Death::Start(UBehaviorTreeComponent& _OwnerComp)
{
	Super::Start(_OwnerComp);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	APawn* SelfPawn = PlayAIData.SelfPawn;
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfPawn);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}

	RotateToTargetActor(_OwnerComp, 0.1f);

	DeathTime = 2.0f;

	if (IsValid(EnemyCharacter))
	{
		EnemyCharacter->DeathPlaySound();
	}
	
	
}

void UBTTaskNode_Death::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	APawn* SelfPawn = PlayAIData.SelfPawn;
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfPawn);

	UCapsuleComponent* Capsule = EnemyCharacter->GetCapsuleComponent();
	if (IsValid(Capsule) && IsValid(EnemyCharacter))
	{
		Capsule->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		EnemyCharacter->GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	
	DeathTime -= _DeltaSeconds;

	if (DeathTime < 0.0f)
	{
		if (!IsValid(EnemyCharacter)) return;
		
		EnemyCharacter->Destroy();
	}


	if (IsValid(EnemyCharacter))
	{
		EnemyCharacter->GetMovementComponent()->StopMovementImmediately();
	}
}


