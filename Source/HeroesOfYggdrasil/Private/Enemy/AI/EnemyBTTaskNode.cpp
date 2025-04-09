// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/AI/EnemyBTTaskNode.h"

#include "BehaviorTree/BTTaskNode.h"

#include "Kismet/KismetMathLibrary.h"
#include <Kismet/GameplayStatics.h>

#include "Attribute/CharacterAttributeComponent.h"

#include "BehaviorTree/BlackboardComponent.h"

#include "AIController.h"


UEnemyBTTaskNode::UEnemyBTTaskNode()
{
	bNotifyTick = true;
}

void UEnemyBTTaskNode::Start(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = UEnemyBTTaskNode::GetPlayAIData(_OwnerComp);
	DeathCheckTime = PlayAIData.Data.StandardZeroTime;
	TargetHeroDeath = PlayAIData.Data.HeroDeathTagName;
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

	const float MaxDistance = PlayAIData.Data.TraceRange;

	// 현재 타겟이 유효한지 확인
	if (IsValid(TargetActor))
	{
		AYggCharacter* CurrentTarget = Cast<AYggCharacter>(TargetActor);
		if (IsValid(CurrentTarget))
		{
			UAttributeComponent* Attr = CurrentTarget->GetAttributeComponent();
			if (IsValid(Attr) && !Attr->HasTag(TargetHeroDeath))
			{
				float Distance = FVector::Dist(SelfActor->GetActorLocation(), CurrentTarget->GetActorLocation());
				if (Distance < MaxDistance)
				{
					// 현재 타겟이 유효하고 범위 내면 유지
					return;
				}
			}
		}
	}

	// 유효하지 않으면 새 타겟 찾기
	TArray<AActor*> AllActors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);

	AActor* NearestActor = nullptr;
	float ClosestDistance = TNumericLimits<float>::Max();

	for (AActor* Actor : AllActors)
	{
		AYggCharacter* CheckCharacter = Cast<AYggCharacter>(Actor);
		if (!IsValid(CheckCharacter)) continue;

		UCharacterAttributeComponent* Attr = CheckCharacter->GetAttributeComponent();
		if (!IsValid(Attr)) continue;
		if (!Attr->HasTag(TEXT("Character"))) continue;
		if (Attr->HasTag(TargetHeroDeath)) continue;

		float Distance = FVector::Dist(SelfActor->GetActorLocation(), CheckCharacter->GetActorLocation());
		if (Distance < MaxDistance && Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			NearestActor = Actor;
		}
	}

	if (IsValid(NearestActor))
	{
		PlayAIData.TargetActor = NearestActor;
	}
}



void UEnemyBTTaskNode::YggdrasilCheck(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = GetPlayAIData(_OwnerComp);

	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;
	AYggCharacter* YggCharacter = Cast<AYggCharacter>(TargetActor);
	
	// 시작시점에 TargetActor가 nullptr 인 경우
	if (!IsValid(TargetActor))
	{
		TArray<AActor*> AllActors;

		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);

		AActor* CheckActor = nullptr;

		for (size_t i = 0; i < AllActors.Num(); i++)
		{
			if (AllActors[i]->GetName().StartsWith(TEXT("BP_Yggdrasil")))
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
	// TargetCharacter의 태그가 "Character.State.Death" 인 경우
	else if (IsValid(YggCharacter))
	{
		UCharacterAttributeComponent* YggCharacterAttributecomponent = YggCharacter->GetAttributeComponent();
		
		if (YggCharacterAttributecomponent->HasTag(TEXT("Character.State.Death")))
		{
			TArray<AActor*> AllActors;

			UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);

			AActor* CheckActor = nullptr;

			for (size_t i = 0; i < AllActors.Num(); i++)
			{
				if (AllActors[i]->GetName().StartsWith(TEXT("BP_Yggdrasil")))
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