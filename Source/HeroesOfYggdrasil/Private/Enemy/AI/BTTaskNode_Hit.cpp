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
	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}
}

void UBTTaskNode_Hit::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	DeathCheck(_OwnerComp);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;

	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfActor);
	if (EnemyCharacter != nullptr)
	{
		UCharacterAttributeComponent* SelfAttributeComponent = EnemyCharacter->GetAttributeComponent();
		if (SelfAttributeComponent != nullptr)
		{
			SelfAttributeComponent->HP;
		}
	}
	

	// 죽음 체크
	
	/*UAttributeComponent* TargetAttributeComponent = TargetActor->FindComponentByClass<UAttributeComponent>();
	TargetAttributeComponent->HasTag("Character");*/
	
}


void UBTTaskNode_Hit::DeathCheck(UBehaviorTreeComponent& _OwnerComp)
{
	Super::DeathCheck(_OwnerComp);
}