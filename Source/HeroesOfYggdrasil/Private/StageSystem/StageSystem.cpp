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
	DOREPLIFETIME(UStageSystem, CurrentStage);
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


