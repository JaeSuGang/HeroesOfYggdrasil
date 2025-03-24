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
	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}
}

void UBTTaskNode_ApproachToAttack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);
	
	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;
	FVector TargetDir = TargetActor->GetActorLocation() - SelfActor->GetActorLocation();
	AAIController* SelfController = SelfActor->GetController<AAIController>();

	// 타겟 null(죽음)
	if (nullptr == TargetActor)
	{
		ChangeState(_OwnerComp, EEnemyAIState::TraceBack);
		return;
	}


	// SelfActor->AddMovementInput(TargetDir);
	ACharacter* SelfCharacter = Cast<ACharacter>(SelfActor);
	SelfCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayAIData.Data.ApproachSpeed;


	if (TargetDir.Size() <= PlayAIData.Data.AttackRange || FName("BP_Yggdrasil") == PlayAIData.TargetActor->GetName().Left(12))
	{
		ChangeState(_OwnerComp, EEnemyAIState::Attack);
		return;
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
