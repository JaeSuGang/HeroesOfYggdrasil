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

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}
}

void UBTTaskNode_Idle::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	DeathCheck(_OwnerComp);

	FPlayAIData& AIData = GetPlayAIData(_OwnerComp);
	APawn* OwningPawn = _OwnerComp.GetAIOwner()->GetPawn();
	AYggCharacter* Enemy = Cast<AYggCharacter>(OwningPawn);

	APawn* SelfActor = AIData.SelfPawn;
	AAIController* SelfController = SelfActor->GetController<AAIController>();
	

	if (!Enemy->GetAttributeComponent()->HasTag("Enemy.DeBuff.Stunned"))
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
