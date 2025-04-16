// Coded By AssortRock Unreal Engine Class Project


#include "Debug/YggCheatManager.h"

#include "StageSystem/StageSystem.h"
#include "UpgradeSystem/UpgradeSystem.h"

void UYggCheatManager::AddUpgradePoint(int a)
{
	if (UUpgradeSystem* UpgradeSystem = UUpgradeSystem::Get(GetWorld()))
	{
		UpgradeSystem->AddUpgradePointInternal(GetOuterAPlayerController()->GetPlayerState<APlayerState>(), a);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%S%u : UpgradeSystem Not Initialized"), __FUNCTION__, __LINE__);
	}
}

void UYggCheatManager::Victory()
{
	if (UStageSystem* StageSystem = UStageSystem::Get(GetOuterAPlayerController()->GetWorld()))
	{
		StageSystem->VictoryInternal();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%S%u : StageSystem Not Initialized"), __FUNCTION__, __LINE__);
	}
}

void UYggCheatManager::Defeat()
{
	if (UStageSystem* StageSystem = UStageSystem::Get(GetOuterAPlayerController()->GetWorld()))
	{
		StageSystem->DefeatInternal();
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%S%u : StageSystem Not Initialized"), __FUNCTION__, __LINE__);
	}
}
