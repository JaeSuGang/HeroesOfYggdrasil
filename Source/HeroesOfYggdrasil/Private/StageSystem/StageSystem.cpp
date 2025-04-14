// Coded By AssortRock Unreal Engine Class Project

#include "StageSystem/StageSystem.h"

#include "GameFramework/GameState.h"
#include "Net/UnrealNetwork.h"

#include "StageSystem/StageBase.h"

UStageSystem::UStageSystem()
{
	bReplicateUsingRegisteredSubObjectList = true;
	SetIsReplicatedByDefault(true);
}


void UStageSystem::BeginPlay()
{
	Super::BeginPlay();

	for (UStageBase* Stage : StageCycle)
	{
		Stage->BeginPlay(this);
	}
}

void UStageSystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UStageSystem, StageCycle);
	DOREPLIFETIME(UStageSystem, CurrentStageIndex);
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
	/* Delegate 인자 설정 */
	FOnExitStageParams OnExitStageParams{};
	OnExitStageParams.PrevRound = CurrentRound;
	OnExitStageParams.NewRound = CurrentRound + 1;

	FOnEnterStageParams OnEnterStageParams{};
	OnEnterStageParams.PrevRound = CurrentRound;
	OnEnterStageParams.NewRound = CurrentRound + 1;

	/* 스테이지 진입과 Delegate 호출 */
	UStageBase* OldStage = StageCycle[CurrentStageIndex];
	OldStage->OnExitStageInternal.Broadcast(OnExitStageParams);

	CurrentStageIndex = ++CurrentStageIndex % StageCycle.Num();
	if (CurrentStageIndex == 0)
	{
		CurrentRound++;
	}

	UStageBase* NewStage = StageCycle[CurrentStageIndex];
	NewStage->Round = CurrentRound;
	NewStage->OnEnterStageInternal.Broadcast(OnEnterStageParams);
}


