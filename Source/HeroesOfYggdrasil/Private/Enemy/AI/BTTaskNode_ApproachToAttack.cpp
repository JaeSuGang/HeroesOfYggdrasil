// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_ApproachToAttack.h"
#include "GameFramework/PawnMovementComponent.h"
#include "AIController.h"

UBTTaskNode_ApproachToAttack::UBTTaskNode_ApproachToAttack()
{
	EnemyAIStateValue = EEnemyAIState::ApproachToAttack;
}

void UBTTaskNode_ApproachToAttack::Start(UBehaviorTreeComponent& _OwnerComp)
{
	Super::Start(_OwnerComp);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}
}

void UBTTaskNode_ApproachToAttack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
	
	DeathCheck(_OwnerComp);
	
	RotateToTargetActor(_OwnerComp, _DeltaSeconds);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	
	APawn* SelfActor = PlayAIData.SelfPawn;

	AActor* TargetActor = PlayAIData.TargetActor;
	AYggCharacter* TargetCharacter = Cast<AYggCharacter>(TargetActor);

	FVector TargetDir = TargetActor->GetActorLocation() - SelfActor->GetActorLocation();

	AAIController* SelfController = SelfActor->GetController<AAIController>();

	// 타겟 히어로 null(죽음)
	if (!IsValid(TargetCharacter))
	{
		return;
	}

	UCharacterAttributeComponent* TargetAttributeComponent = TargetCharacter->GetAttributeComponent();

	if (IsValid(TargetAttributeComponent))
	{
		if (TargetAttributeComponent->HasTag(TargetHeroDeath))
		{
			ChangeState(_OwnerComp, EEnemyAIState::TraceBack);
			return;
		}
	}
	


	// SelfActor->AddMovementInput(TargetDir);
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);
	
	EnemyCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayAIData.Data.ApproachSpeed;
	

	if (TargetDir.Size() <= PlayAIData.Data.AttackRange)
	{
		FString DataKeyStr = EnemyCharacter->GetDataKey();

		// 저주술사인 경우
		if (DataKeyStr.StartsWith(FString("Minion_Witch")))
		{
			ChangeState(_OwnerComp, EEnemyAIState::Await);
			return;
		}
		// 일반적인 캐릭터인 경우
		else
		{
			ChangeState(_OwnerComp, EEnemyAIState::Attack);
			return;
		}
		
	}

	float Size = TargetDir.Size();

	if (Size >= PlayAIData.Data.TraceRange)
	{
		ChangeState(_OwnerComp, EEnemyAIState::TraceBack);
		return;
	}

	if (SelfController != nullptr && TargetActor != nullptr)
	{
		SelfController->MoveToActor(TargetActor, PlayAIData.Data.AttackRange / 2.0f);
	}
}


void UBTTaskNode_ApproachToAttack::RotateToTargetActor(UBehaviorTreeComponent& _OwnerComp, float _DeltaSeconds)
{
	Super::RotateToTargetActor(_OwnerComp, _DeltaSeconds);
}

void UBTTaskNode_ApproachToAttack::DeathCheck(UBehaviorTreeComponent& _OwnerComp)
{
	Super::DeathCheck(_OwnerComp);
}