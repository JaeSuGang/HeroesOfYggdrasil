// Coded By AssortRock Unreal Engine Class Project

#include "StageSystem/StageSystem.h"

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
	UStageBase* OldStage = StageCycle[CurrentStageIndex];
	OldStage->OnExitStageInternal.Broadcast();

	CurrentStageIndex = ++CurrentStageIndex % StageCycle.Num();
	if (CurrentStageIndex == 0)
	{
		CurrentRound++;
	}

	UStageBase* NewStage = StageCycle[CurrentStageIndex];
	NewStage->Round = CurrentRound;
	NewStage->OnEnterStageInternal.Broadcast();
}


