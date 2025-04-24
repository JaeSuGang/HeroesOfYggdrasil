// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_Trace.h"
#include "Enemy/EnemyAnimCharacter.h"
#include "AIController.h"

UBTTaskNode_Trace::UBTTaskNode_Trace()
{
	EnemyAIStateValue = EEnemyAIState::Trace;
}

void UBTTaskNode_Trace::Start(UBehaviorTreeComponent& _OwnerComp)
{
	Super::Start(_OwnerComp);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}
	CheckTime = PlayAIData.Data.StandardZeroTime;
}

void UBTTaskNode_Trace::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	DeathCheck(_OwnerComp);

	RotateToTargetActor(_OwnerComp, _DeltaSeconds);

	CheckTime -= _DeltaSeconds;

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	AActor* TargetActor = PlayAIData.TargetActor;
	AYggCharacter* TargetCharacter = Cast<AYggCharacter>(TargetActor);
	APawn* SelfActor = PlayAIData.SelfPawn;
	
	if (!IsValid(TargetCharacter))
	{
		return;
	}

	UCharacterAttributeComponent* TargetAttributeComponent = TargetCharacter->GetAttributeComponent();
	// 히어로 사망 체크
	if (IsValid(TargetAttributeComponent))
	{
		if (TargetAttributeComponent->HasTag(TargetHeroDeath))
		{
			ChangeState(_OwnerComp, EEnemyAIState::TraceBack);
			return;
		}
	}
	


	FVector TargetDir = TargetActor->GetActorLocation() - SelfActor->GetActorLocation();

	ACharacter* SelfCharacter = Cast<ACharacter>(SelfActor);
	SelfCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayAIData.Data.TraceSpeed;

	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);

	if (EnemyCharacter->GetAttributeComponent()->HasTag(TEXT("Enemy.Debuff.Stunned"))) {
		ChangeState(_OwnerComp, EEnemyAIState::Idle);
		return;
	}

	if (EnemyCharacter->GetAttributeComponent()->HasTag(TEXT("Enemy.State.Hit"))) {
		EnemyCharacter->ClearHitState();
		ChangeState(_OwnerComp, EEnemyAIState::Hit);
		return;
	}

	// 공격준비
	if (TargetDir.Size() <= PlayAIData.Data.StrafeRange)
	{
		ChangeState(_OwnerComp, EEnemyAIState::Strafe);
		return;
	}

	AAIController* SelfController = SelfActor->GetController<AAIController>();
	// 추적
	if (SelfController != nullptr && TargetActor!= nullptr && CheckTime < 0.0f)
	{
		SelfController->MoveToActor(TargetActor);
		CheckTime = PlayAIData.Data.TargetCheckTime;
	}
	
	// 복귀
	float Size = TargetDir.Size();
	if (Size >= PlayAIData.Data.TraceRange)
	{
		ChangeState(_OwnerComp, EEnemyAIState::TraceBack);
		return;
	}
}

void UBTTaskNode_Trace::RotateToTargetActor(UBehaviorTreeComponent& _OwnerComp, float _DeltaSeconds)
{
	Super::RotateToTargetActor(_OwnerComp, _DeltaSeconds);
}


void UBTTaskNode_Trace::DeathCheck(UBehaviorTreeComponent& _OwnerComp)
{
	Super::DeathCheck(_OwnerComp);
}

