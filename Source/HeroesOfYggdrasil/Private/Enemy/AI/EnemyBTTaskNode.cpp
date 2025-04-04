// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/EnemyBTTaskNode.h"
#include "BehaviorTree/BTTaskNode.h"
#include <Kismet/GameplayStatics.h>
#include "BehaviorTree/BlackboardComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "AIController.h"


UEnemyBTTaskNode::UEnemyBTTaskNode()
{
	bNotifyTick = true;
}

void UEnemyBTTaskNode::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	DeathCheckTime = PlayAIData.Data.StandardZeroTime;
}

EBTNodeResult::Type UEnemyBTTaskNode::ExecuteTask(UBehaviorTreeComponent& _OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(_OwnerComp, NodeMemory);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	if (PlayAIData.EnemyAIState != EnemyAIStateValue)
	{
		return EBTNodeResult::Type::Failed;
	}

	Start(_OwnerComp);

	return EBTNodeResult::Type::InProgress;
}

void UEnemyBTTaskNode::TickTask(UBehaviorTreeComponent& _OwnerComp, uint8* _pNodeMemory, float _DeltaSeconds)
{
	Super::TickTask(_OwnerComp, _pNodeMemory, _DeltaSeconds);

	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);

	DeathCheckTime -= _DeltaSeconds;
}

void UEnemyBTTaskNode::ChangeState(UBehaviorTreeComponent& _OwnerComp, EEnemyAIState _State)
{
	FPlayAIData& PlayAIData = GetPlayAIData(_OwnerComp);
	PlayAIData.EnemyAIState = _State;
	FinishLatentTask(_OwnerComp, EBTNodeResult::Failed);
}

FPlayAIData& UEnemyBTTaskNode::GetPlayAIData(UBehaviorTreeComponent& _OwnerComp)
{
	UObject* AIData = _OwnerComp.GetBlackboardComponent()->GetValueAsObject(UEnemyConst::AI::EnemyAIDataName);
	return Cast<UAIDataObject>(AIData)->PlayData;
}

TArray<AActor*> OutActors;

void UEnemyBTTaskNode::TargetCheck(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = GetPlayAIData(_OwnerComp);

	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;

	if (nullptr == TargetActor || FName("BP_Yggdrasil") == PlayAIData.TargetActor->GetName().Left(12))
	{
		//UGameplayStatics::GetAllActorsWithTag(GetWorld(), TEXT("Character"), OutActors);

		/*
		float CurTargetDistance = TNumericLimits<float>::Max();
		for (size_t i = 0; i < OutActors.Num(); i++)
		{
			CheckActor = OutActors[i];
			float TargetDis = (SelfActor->GetActorLocation() - CheckActor->GetActorLocation()).Size();
			if (TargetDis < PlayAIData.Data.TraceRange && TargetDis < CurTargetDistance)
			{
				TargetActor = CheckActor;
			}
		}
		*/

		// 태그 확인되면 수정 에정 

		TArray<AActor*> AllActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);

	
		AActor* CheckActor = nullptr;
		float CurTargetDistance = TNumericLimits<float>::Max();
		for (size_t i = 0; i < AllActors.Num(); i++)
		{
			if (FName("BP_YggHero") == AllActors[i]->GetName().Left(10))
			{
				CheckActor = AllActors[i];
				float TargetDis = (SelfActor->GetActorLocation() - CheckActor->GetActorLocation()).Size();
				if (TargetDis < PlayAIData.Data.TraceRange && TargetDis < CurTargetDistance)
				{
					TargetActor = CheckActor;
				}
			}
		}

		if (nullptr != TargetActor)
		{
			PlayAIData.TargetActor = TargetActor;
		}
	}
}


void UEnemyBTTaskNode::YggdrasilCheck(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = GetPlayAIData(_OwnerComp);

	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;

	if (nullptr == TargetActor)
	{
		TArray<AActor*> AllActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);


		AActor* CheckActor = nullptr;
		float CurTargetDistance = TNumericLimits<float>::Max();
		for (size_t i = 0; i < AllActors.Num(); i++)
		{
			if (FName("BP_Yggdrasil") == AllActors[i]->GetName().Left(12))
			{
				CheckActor = AllActors[i];
				TargetActor = CheckActor;
			}
		}

		if (nullptr != TargetActor)
		{
			PlayAIData.TargetActor = TargetActor;
		}
	}
}

void UEnemyBTTaskNode::RotateToTargetActor(UBehaviorTreeComponent& _OwnerComp, float _DeltaSeconds)
{

	FPlayAIData& PlayAIData = GetPlayAIData(_OwnerComp);

	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;

	APawn* OwningPawn = _OwnerComp.GetAIOwner()->GetPawn();

	if (OwningPawn && TargetActor)
	{
		if (FName("BP_YggHero") == TargetActor->GetName().Left(10) || FName("BP_Yggdrasil") == TargetActor->GetName().Left(12))
		{
			const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(OwningPawn->GetActorLocation(), TargetActor->GetActorLocation());
			FRotator TargetRot = FMath::RInterpTo(OwningPawn->GetActorRotation(), LookAtRot, _DeltaSeconds, RotationInterSpeed);
			TargetRot.Pitch = 0.0f;
			OwningPawn->SetActorRotation(TargetRot);
		}
	}
}



void UEnemyBTTaskNode::DeathCheck(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = GetPlayAIData(_OwnerComp);
	APawn* SelfPawn = PlayAIData.SelfPawn;
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfPawn);

	UCharacterAttributeComponent* EnemyAttributeComponent =  EnemyCharacter->GetAttributeComponent();
	
	if (EnemyAttributeComponent->HP <= 0.0f)
	{
		if (EnemyCharacter != nullptr)
		{
			ChangeState(_OwnerComp, EEnemyAIState::Death);
			return;
		}
	}


}