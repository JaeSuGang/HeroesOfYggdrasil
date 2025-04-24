// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_TraceYggdrasil.h"


UBTTaskNode_TraceYggdrasil::UBTTaskNode_TraceYggdrasil()
{
	EnemyAIStateValue = EEnemyAIState::TraceYggdrasil;
}

void UBTTaskNode_TraceYggdrasil::Start(UBehaviorTreeComponent& _OwnerComp)
{
	Super::Start(_OwnerComp);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}

	// 시작할 때 타겟 이그드라실 세팅
	YggdrasilCheck(_OwnerComp);

	CheckTime = PlayAIData.Data.StandardZeroTime;

}

void UBTTaskNode_TraceYggdrasil::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
	
	DeathCheck(_OwnerComp);

	CheckTime -= _DeltaSeconds;

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	AActor* TargetActor = PlayAIData.TargetActor;
	AYggCharacter* TargetCharacter = Cast<AYggCharacter>(TargetActor);

	

	APawn* SelfActor = PlayAIData.SelfPawn;
	FVector TargetDir = TargetActor->GetActorLocation() - SelfActor->GetActorLocation();
	TargetDir.Z = 0.0f;
	
	AEnemyAIController* SelfController = SelfActor->GetController<AEnemyAIController>();
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);

	float ReturnSize = TargetDir.Size() - 100.0f;


	// 이동 중 플레이어 타겟 체크
	TargetCheck(_OwnerComp);

	// 이그드라실 null(죽음) -> 추후 수정
	if (nullptr == TargetActor)
	{
		ChangeState(_OwnerComp, EEnemyAIState::Idle);
		return;
	}
	

	// 감지 범위 안에 플레이어 들어오면 플레이어 추적

	if (IsValid(TargetCharacter))
	{
		UCharacterAttributeComponent* TargetAttributeComponent = TargetCharacter->GetAttributeComponent();
		if (IsValid(TargetAttributeComponent))
		{
			if (TargetAttributeComponent->HasTag(TEXT("Character")))
			{
				PlayAIData.OriginPos = SelfActor->GetActorLocation();
				ChangeState(_OwnerComp, EEnemyAIState::Trace);
				return;

			}
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



	// 공격준비
	if (ReturnSize <= (PlayAIData.Data.YggAttackRange) * 1.1f )
	{
		ChangeState(_OwnerComp, EEnemyAIState::Attack);
		return;
	}

	// 이그드라실 추적
	if (IsValid(SelfController) && IsValid(TargetActor))
	{
		FVector TargetVector = TargetActor->GetActorLocation();
		TargetVector.Z = 0.0f;
		FVector SelfLocation = SelfActor->GetActorLocation();

		FVector Location = TargetVector - SelfLocation;

		float Size = Location.Size();

		SelfController->MoveToLocation(TargetVector, PlayAIData.Data.YggAttackRange);
	}
}

void UBTTaskNode_TraceYggdrasil::DeathCheck(UBehaviorTreeComponent& _OwnerComp)
{
	Super::DeathCheck(_OwnerComp);
}


