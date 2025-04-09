// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_Attack.h"
#include "Enemy/EnemyWarningRange.h"


UBTTaskNode_Attack::UBTTaskNode_Attack()
{
	EnemyAIStateValue = EEnemyAIState::Attack;
}

void UBTTaskNode_Attack::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;
	TargetRangeLocation = TargetActor->GetActorLocation();



	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}

	AttackTime = PlayAIData.Data.AttackTime;

	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);
	
	// 궁수면 화살 보이게
	if (EnemyCharacter != nullptr)
	{
		FString DataKeyStr = EnemyCharacter->GetDataKey();

		// 미니언 궁수
		if (FString("Minion_Archer") == DataKeyStr)
		{
			EnemyCharacter->RevealArrow();
		}

		// 저주술사
		if (FString("Minion_Witch") == DataKeyStr)
		{
			EnemyCharacter->SpawnWarningRange(TargetActor);
		}
	}

	// 타겟 죽음 체크
	AYggCharacter* TargetCharacter = Cast<AYggCharacter>(TargetActor);
	UCharacterAttributeComponent* TargetAttributecomponent = TargetCharacter->GetAttributeComponent();
	if (IsValid(TargetAttributecomponent))
	{
		if (TargetAttributecomponent->HasTag(TEXT("Character.state.Death")))
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

	FString DataKeyString = EnemyCharacter->GetDataKey();

	// 타겟 죽음 체크

	


	// 저주술사
	if (FString("Minion_Witch") == DataKeyString)
	{
	}

	if (SelfController)
	{
		SelfController->StopMovement();
	}

	AttackTime -= _DeltaSeconds;

	if (AttackTime < PlayAIData.Data.StandardZeroTime)
	{
		
		
		// 미니언 궁수
		if (FString("Minion_Archer") == DataKeyString)
		{
			EnemyCharacter->SpawnAndFireArrow();
			EnemyCharacter->HideArrow();
		}
		// 저주술사
		if (FString("Minion_Witch") == DataKeyString)
		{
			EnemyCharacter->ThrowPoisonedBall(TargetRangeLocation);
		}

		ChangeState(_OwnerComp, EEnemyAIState::Await);
		AttackTime = PlayAIData.Data.AttackTime;
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