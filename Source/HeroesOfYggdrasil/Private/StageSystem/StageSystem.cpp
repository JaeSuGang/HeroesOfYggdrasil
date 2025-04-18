// Coded By AssortRock Unreal Engine Class Project

#include "StageSystem/StageSystem.h"

#include "EngineUtils.h"
#include "GameFramework/GameState.h"
#include "Net/UnrealNetwork.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

#include "StageSystem/StageBase.h"
#include "StageSystem/Stages/BattleStage.h"
#include "StageSystem/Stages/ReinforceStage.h"
#include "MainGame/UI/MainGameHUD.h"

UStageSystem::UStageSystem()
{
	bReplicateUsingRegisteredSubObjectList = true;
	SetIsReplicatedByDefault(true);
}

UStageSystem* UStageSystem::Get(UObject* WorldContextObject)
{
	if (AGameState* GameState = WorldContextObject->GetWorld()->GetGameState<AGameState>())
	{
		UStageSystem* StageSystem = GameState->GetComponentByClass<UStageSystem>();
		return StageSystem;
	}

	return nullptr;
}

void UStageSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentRound > 0)
	{
		StageCycle[CurrentStageIndex]->TickLogic(DeltaTime);
	}

	Timer -= DeltaTime;
	if (Timer < 0.0f)
		Timer = 0.0f;
}

void UStageSystem::BeginPlay()
{
	Super::BeginPlay();

	for (TActorIterator<ALevelSequenceActor> Iter(GetWorld()); Iter; ++Iter)
	{
		LevelSequenceActor = *Iter;
		break;
	}

	for (UStageBase* Stage : StageCycle)
	{
		Stage->BeginPlay(this);
	}

	OnDefeated.AddDynamic(this, &UStageSystem::PlayDefeatLevelSequence);
}

void UStageSystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UStageSystem, StageCycle);
	DOREPLIFETIME(UStageSystem, CurrentStageIndex);
	DOREPLIFETIME(UStageSystem, CurrentRound);
	DOREPLIFETIME(UStageSystem, Timer);
}

void UStageSystem::RegisterObjectsToReplicate()
{
	for (UStageBase* Stage : StageCycle)
	{
		AddReplicatedSubObject(Stage);
	}
}

void UStageSystem::UnregisterObjectsToReplicate()
{
	for (UStageBase* Stage : StageCycle)
	{
		RemoveReplicatedSubObject(Stage);
	}
}

void UStageSystem::VictoryInternal()
{
	if (GetOwner()->HasAuthority())
	{
		UE_LOG(LogTemp, Error, TEXT("%S%u : Victory!"), __FUNCTION__, __LINE__);

		MulticastVictory(FOnVictoryParams{});
	}
}

void UStageSystem::DefeatInternal()
{
	if (GetOwner()->HasAuthority())
	{
		UE_LOG(LogTemp, Error, TEXT("%S%u : Defeated!"), __FUNCTION__, __LINE__);

		MulticastDefeated(FOnDefeatedParams{});
	}
}

void UStageSystem::MulticastDefeated_Implementation(FOnDefeatedParams OnDefeatedParams)
{
	OnDefeated.Broadcast(OnDefeatedParams);
}

void UStageSystem::MulticastVictory_Implementation(FOnVictoryParams OnVictoryParams)
{
	OnVictory.Broadcast(OnVictoryParams);
}

void UStageSystem::StartGame()												
{
	if (GetOwner()->HasAuthority())
	{
		EnterStage(0);

		BroadcastGameStart(FOnGameStartParams{});
	}
}

void UStageSystem::BroadcastGameStart_Implementation(FOnGameStartParams OnGameStartParams)
{
	OnGameStarted.Broadcast(OnGameStartParams);
}

void UStageSystem::EnterNextStage()
{
	EnterStage(CurrentStageIndex + 1);
}

void UStageSystem::EnterStage(int NewStageIndex)
{
	if (GetOwner()->HasAuthority())
	{
		EnterStageInternal(NewStageIndex);
	}
	else
	{
		RequestEnterStage(NewStageIndex);
	}
}

void UStageSystem::RequestEnterStage_Implementation(int NewStageIndex)
{
	EnterStageInternal(NewStageIndex);
}

void UStageSystem::EnterStageInternal(int NewStageIndex)
{
	int OldStageIndex = CurrentStageIndex;

	CurrentStageIndex = NewStageIndex % StageCycle.Num();
	if (CurrentStageIndex == 0)
	{
		CurrentRound++;
	}

	/* Delegate 인자 설정 */
	FOnExitStageParams OnExitStageParams{};
	OnExitStageParams.NewRound = CurrentRound;

	FOnEnterStageParams OnEnterStageParams{};
	OnEnterStageParams.NewRound = CurrentRound;

	/* 스테이지 진입과 Delegate 호출 */
	UStageBase* OldStage = StageCycle[OldStageIndex];
	OldStage->OnExitStageInternal.Broadcast(OnExitStageParams);

	UStageBase* NewStage = StageCycle[CurrentStageIndex];
	NewStage->OnEnterStageInternal.Broadcast(OnEnterStageParams);
}

UBattleStage* UStageSystem::GetBattleStage() const
{
	for (UStageBase* Stage : StageCycle)
	{
		if (UBattleStage* CastedStage = Cast<UBattleStage>(Stage))
		{
			return CastedStage;
		}
	}
	return nullptr;
}

UReinforceStage* UStageSystem::GetReinforceStage() const
{
	for (UStageBase* Stage : StageCycle)
	{
		if (UReinforceStage* CastedStage = Cast<UReinforceStage>(Stage))
		{
			return CastedStage;
		}
	}
	return nullptr;
}

void UStageSystem::PlayDefeatLevelSequence(FOnDefeatedParams OnDefeatedParams)
{
	if (LevelSequenceActor)
	{
		LevelSequenceActor->GetSequencePlayer()->Play();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("%S%u : LevelSequenceActor Not Defined!"), __FUNCTION__, __LINE__);
	}
}


