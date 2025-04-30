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
	APawn* OwningPawn = _OwnerComp.GetAIOwner()->GetPawn();
	AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OwningPawn);
	AActor* TargetActor = PlayAIData.TargetActor;

	DeathCheckTime -= _DeltaSeconds;

	if (APlayerController* PC = UGameplayStatics::GetPlayerController(PlayAIData.SelfPawn, 0))
	{
		if (PC->IsInputKeyDown(EKeys::O))
		{
			ChangeState(_OwnerComp, EEnemyAIState::Idle);
		}
		if (PC->IsInputKeyDown(EKeys::L))
		{
			ChangeState(_OwnerComp, EEnemyAIState::TraceYggdrasil);
		}
		if (PC->IsInputKeyDown(EKeys::P))
		{
			Enemy->GetAttributeComponent()->AddTag(TEXT("Enemy.DeBuff.Stunned"));
		}
		if (PC->IsInputKeyDown(EKeys::U))
		{
			Enemy->GetAttributeComponent()->RemoveTag(TEXT("Enemy.DeBuff.Stunned"));
		}
	}
}

void UEnemyBTTaskNode::ChangeState(UBehaviorTreeComponent& _OwnerComp, EEnemyAIState _State)
{
	AController* AIC = _OwnerComp.GetAIOwner();
	if (!IsValid(AIC) || !IsValid(AIC->GetPawn())) return;

	FPlayAIData& PlayAIData = GetPlayAIData(_OwnerComp);
	APawn* OwningPawn = _OwnerComp.GetAIOwner()->GetPawn();
	PlayAIData.EnemyAIState = _State;
	if (IsValid(OwningPawn))
	{
		FinishLatentTask(_OwnerComp, EBTNodeResult::Failed);
	}
}

FPlayAIData& UEnemyBTTaskNode::GetPlayAIData(UBehaviorTreeComponent& _OwnerComp)
{
	UObject* AIData = _OwnerComp.GetBlackboardComponent()->GetValueAsObject(UEnemyConst::AI::EnemyAIDataName);
	return Cast<UAIDataObject>(AIData)->PlayData;
}

void UEnemyBTTaskNode::TargetCheck(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = GetPlayAIData(_OwnerComp);

	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;
	const float MaxDistance = PlayAIData.Data.TraceRange;

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
					return;
				}
			}
		}
	}

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

	if (!_OwnerComp.IsValidLowLevel()) return;

	FPlayAIData& PlayAIData = GetPlayAIData(_OwnerComp);

	APawn* SelfActor = PlayAIData.SelfPawn;
	AActor* TargetActor = PlayAIData.TargetActor;
	AYggCharacter* YggCharacter = Cast<AYggCharacter>(TargetActor);

	if (!IsValid(TargetActor) || (IsValid(YggCharacter) && YggCharacter->GetAttributeComponent()->HasTag(TEXT("Character.State.Death"))))
	{
		TArray<AActor*> AllActors;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AActor::StaticClass(), AllActors);

		for (AActor* Actor : AllActors)
		{
			if (Actor->GetName().StartsWith(TEXT("BP_Yggdrasil")))
			{
				PlayAIData.TargetActor = Actor;
				break;
			}
		}
	}
}

void UEnemyBTTaskNode::RotateToTargetActor(UBehaviorTreeComponent& _OwnerComp, float _DeltaSeconds)
{
	if (!_OwnerComp.IsValidLowLevel()) return;

	FPlayAIData& PlayAIData = GetPlayAIData(_OwnerComp);

	APawn* OwningPawn = _OwnerComp.GetAIOwner()->GetPawn();
	AActor* TargetActor = PlayAIData.TargetActor;
	AYggCharacter* TargetCharacter = Cast<AYggCharacter>(TargetActor);

	if (!IsValid(OwningPawn) || !IsValid(TargetActor)|| !IsValid(TargetCharacter)) return;

	const FString TargetName = TargetActor->GetName();

	if (IsValid(TargetCharacter))
	{
		UCharacterAttributeComponent* TargetAttributecom = TargetCharacter->GetAttributeComponent();

		if (!IsValid(TargetAttributecom)) return;

		if (TargetName.StartsWith(TEXT("BP_YggHero")) || TargetName.StartsWith(TEXT("BP_Yggdrasil")) || TargetCharacter->GetAttributeComponent()->HasTag(TEXT("Character")))
		{
			const FVector PawnLoc = OwningPawn->GetActorLocation();
			const FVector TargetLoc = TargetActor->GetActorLocation();

			const FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(PawnLoc, TargetLoc);

			FRotator CurrentRot = OwningPawn->GetActorRotation();
			FRotator TargetRot = FMath::RInterpTo(CurrentRot, LookAtRot, _DeltaSeconds, RotationInterSpeed);

			TargetRot.Pitch = 0.f;
			TargetRot.Roll = 0.f;

			OwningPawn->SetActorRotation(TargetRot);
		}
	}

	
}

void UEnemyBTTaskNode::DeathCheck(UBehaviorTreeComponent& _OwnerComp)
{
	FPlayAIData& PlayAIData = GetPlayAIData(_OwnerComp);
	APawn* SelfPawn = PlayAIData.SelfPawn;
	AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(SelfPawn);

	UCharacterAttributeComponent* EnemyAttributeComponent = EnemyCharacter->GetAttributeComponent();

	if (EnemyAttributeComponent->HP <= 0.0f)
	{
		if (EnemyCharacter != nullptr)
		{
			ChangeState(_OwnerComp, EEnemyAIState::Death);
			return;
		}
	}
}
