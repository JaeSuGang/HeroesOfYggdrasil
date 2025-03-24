// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_Hit.h"
#include "GameFramework/Actor.h"

UBTTaskNode_Hit::UBTTaskNode_Hit()
{
	EnemyAIStateValue = EEnemyAIState::Hit;
}

void UBTTaskNode_Hit::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}
}

void UBTTaskNode_Hit::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;

	// 죽음 체크
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);
	/*UAttributeComponent* TargetAttributeComponent = TargetActor->FindComponentByClass<UAttributeComponent>();
	TargetAttributeComponent->HasTag("Character");*/
	
}
