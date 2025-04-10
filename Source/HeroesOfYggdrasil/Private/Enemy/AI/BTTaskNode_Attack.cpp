// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_Attack.h"
#include "Enemy/EnemyWarningRange.h"


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
	TargetRangeLocation = TargetActor->GetActorLocation();



	if (IsValid(SelfActor))
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}

	AttackTime = PlayAIData.Data.AttackTime;

	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);
	
	// 궁수면 화살 보이게
	if (IsValid(EnemyCharacter))
	{
		FString DataKeyStr = EnemyCharacter->GetDataKey();

		// 미니언 궁수
		if (DataKeyStr.StartsWith(FString("Minion_Archer")))
		{
			EnemyCharacter->RevealArrow();
		}

		// 저주술사
		if (DataKeyStr.StartsWith(FString("Minion_Witch")))
		{
			EnemyCharacter->SpawnWarningRange(TargetActor);
		}
	}

	// 타겟 죽음 체크
	AYggCharacter* TargetCharacter = Cast<AYggCharacter>(TargetActor);

	 // 이그드라실일 경우
	if (!IsValid(TargetCharacter))
	{
		return;
	}

	// 히어로인 경우
	UCharacterAttributeComponent* TargetAttributecomponent = TargetCharacter->GetAttributeComponent();
	if (IsValid(TargetAttributecomponent))
	{
		if (TargetAttributecomponent->HasTag(TargetHeroDeath))
		{
			ChangeState(_OwnerComp,EEnemyAIState::TraceYggdrasil);
			return;
		}

	}
	
}

void UBTTaskNode_Attack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	DeathCheck(_OwnerComp);

	RotateToTargetActor(_OwnerComp, _DeltaSeconds);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	
	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);
	AAIController* SelfController = SelfActor->GetController<AAIController>();

	FString DataKeyStr = EnemyCharacter->GetDataKey();

	if (SelfController)
	{
		SelfController->StopMovement();
	}

	AttackTime -= _DeltaSeconds;

	if (AttackTime < PlayAIData.Data.StandardZeroTime)
	{
		
		
		// 미니언 궁수
		if (DataKeyStr.StartsWith(FString("Minion_Archer")))
		{
			EnemyCharacter->SpawnAndFireArrow();
			EnemyCharacter->HideArrow();
		}

		// 저주술사
		if (DataKeyStr.StartsWith(FString("Minion_Witch")))
		{
			EnemyCharacter->ThrowPoisonedBall(TargetRangeLocation);
		}

		AttackTime = PlayAIData.Data.AttackTime;
		ChangeState(_OwnerComp, EEnemyAIState::Await);
		return;
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