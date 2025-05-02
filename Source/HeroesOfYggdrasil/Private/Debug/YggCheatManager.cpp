// Coded By AssortRock Unreal Engine Class Project


#include "Debug/YggCheatManager.h"

#include "EngineUtils.h"
#include "StageSystem/StageSystem.h"
#include "UpgradeSystem/UpgradeSystem.h"
#include "Attribute/HeroAttributeComponent.h"
#include "Attribute/CharacterAttributeComponent.h"
#include "MainGame/MainGamePlayerState.h"
#include "StageSystem/StageSystem.h"
#include "NPC/Yggdrasil.h"
#include "Player/YggHero.h"

void UYggCheatManager::InvincibleAll()
{
	for (TActorIterator<AYggdrasil> Iter(GetWorld()); Iter; ++Iter)
	{
		if (UCharacterAttributeComponent* UAC = Cast<UCharacterAttributeComponent>((*Iter)->GetAttributeComponent()))
		{
			UAC->Server_SetMaxHP(999999.0f);
			UAC->Server_SetHP(999999.0f);
			break;
		}
	}
	for (TActorIterator<AYggHero> Iter(GetWorld()); Iter; ++Iter)
	{
		if (UCharacterAttributeComponent* UAC = Cast<UCharacterAttributeComponent>((*Iter)->GetAttributeComponent()))
		{
			UAC->Server_SetMaxHP(999999.0f);
			UAC->Server_SetHP(999999.0f);
			UAC->Server_SetAttackPoints(300.0f);
		}
	}
}

void UYggCheatManager::EnterBattleStage(int RoundNumber)
{
	if (UStageSystem* StageSystem = UStageSystem::Get(this))
	{
		ensure(StageSystem->GetOwner()->HasAuthority());
		
		StageSystem->CurrentRound = RoundNumber;
		StageSystem->EnterStage(1);
	}
}

void UYggCheatManager::Upgrade(int index)
{
	if (UUpgradeSystem* UpgradeSystem = UUpgradeSystem::Get(GetWorld()))
	{
		UHeroAttributeComponent* AC = GetOuterAPlayerController()->GetPawn()->GetComponentByClass<UHeroAttributeComponent>();
		AMainGamePlayerState* MPS = GetOuterAPlayerController()->GetPlayerState<AMainGamePlayerState>();
		if (index < MPS->AvailableUpgradeIds.Num())
		{
			UpgradeSystem->UpgradeByUpgradeId(AC, MPS->AvailableUpgradeIds[index]);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%S%u : Invalid Index For Upgrade"), __FUNCTION__, __LINE__);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%S%u : UpgradeSystem Not Initialized"), __FUNCTION__, __LINE__);
	}
}

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
