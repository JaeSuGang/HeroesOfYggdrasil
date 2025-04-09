// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/BTTaskNode_TraceBack.h"
#include "Enemy/EnemyCharacter.h"

UBTTaskNode_TraceBack::UBTTaskNode_TraceBack()
{
	EnemyAIStateValue = EEnemyAIState::TraceBack;
}

void UBTTaskNode_TraceBack::Start(UBehaviorTreeComponent& _OwnerComp)
{
	Super::Start(_OwnerComp);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	if (nullptr != PlayAIData.SelfAnimPawn)
	{
		PlayAIData.SelfAnimPawn->ChangeAnimation_Multicast(static_cast<int>(EnemyAIStateValue));
	}
}

void UBTTaskNode_TraceBack::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	DeathCheck(_OwnerComp);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	APawn* SelfActor = PlayAIData.SelfPawn;
	ACharacter* SelfCharacter = Cast<ACharacter>(SelfActor);
	FVector OrigninDir = PlayAIData.OriginPos - SelfActor->GetActorLocation();

	SelfCharacter->GetCharacterMovement()->MaxWalkSpeed = PlayAIData.Data.TraceBackSpeed;


	// 기존 위치로 이동
	AEnemyAIController* SelfController = SelfActor->GetController<AEnemyAIController>();
	if (IsValid(SelfController))
	{
		SelfController->MoveToLocation(PlayAIData.OriginPos, 50.0f);
	}
	

	float OrigninDirSize = OrigninDir.Size();

	if (OrigninDir.Size() < 300.0f)
	{
		PlayAIData.TargetActor = nullptr;
		ChangeState(_OwnerComp, EEnemyAIState::TraceYggdrasil);
		return;
	}
}

void UBTTaskNode_TraceBack::DeathCheck(UBehaviorTreeComponent& _OwnerComp)
{
	Super::DeathCheck(_OwnerComp);
}

