// Coded By AssortRock Unreal Engine Class Project

#include "StageSystem/StageSystem.h"

#include "Net/UnrealNetwork.h"

UStageSystem::UStageSystem()
{
	SetIsReplicatedByDefault(true);
}


void UStageSystem::BeginPlay()
{
	Super::BeginPlay();

}

void UStageSystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UStageSystem, CurrentStage);
}


