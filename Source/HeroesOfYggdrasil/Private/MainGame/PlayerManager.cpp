// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/PlayerManager.h"

#include "Math/UnrealMathUtility.h"
#include "Algo/RandomShuffle.h"

#include "MainGame/MainGameState.h"
#include "MainGame/MainGamePlayerState.h"
#include "Player/YggHero.h"
#include "Attribute/HeroAttributeComponent.h"
#include "Upgrade/Upgrades.h"

APlayerManager::APlayerManager()
{
	bReplicates = true;
	bAlwaysRelevant = true;
	NetDormancy = DORM_Never;
}

APlayerManager* APlayerManager::Get(UWorld* WorldContext)
{
	if (AMainGameState* MGS = WorldContext->GetGameState<AMainGameState>())
	{
		return MGS->PlayerManager;
	}

	return nullptr;
}

AMainGamePlayerState* APlayerManager::GetPlayerState(APlayerController* PC)
{
	return PC->GetPlayerState<AMainGamePlayerState>();
}

void APlayerManager::BeginPlay()
{
	Super::BeginPlay();

	SetHeroUpgradesFromTable();
}

void APlayerManager::Server_SelectUpgrade_Implementation(APlayerController* PC, int nChoiceIndex)
{
	if (AMainGamePlayerState* MPS = PC->GetPlayerState<AMainGamePlayerState>())
	{
		if (nChoiceIndex < MPS->AvailableHeroUpgrades.Num())
		{
			MPS->AvailableHeroUpgrades[nChoiceIndex]->Apply(PC, 0.0f);
			MPS->AvailableHeroUpgrades.Empty();
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%S%u : Choice Index Larger than available."), __FUNCTION__, __LINE__);
		}
	}

}

void APlayerManager::Server_GenerateAvailableUpgradesForPlayer_Implementation(APlayerController* PC, int nChoices)
{
	if (AMainGamePlayerState* MPS = PC->GetPlayerState<AMainGamePlayerState>())
	{
		/* 업그레이드 가능 목록 리셋 */
		MPS->AvailableHeroUpgrades.Empty();

		/* 랜덤 알고리즘 */
		TArray<int> IndexesToUse{};
		for (int i = 0; i < HeroUpgrades.Num(); ++i)
		{
			IndexesToUse.Add(i);
		}

		Algo::RandomShuffle<TArray<int>>(IndexesToUse);

		/* 업그레이드 목록 설정 */
		for (int i = 0; i < nChoices; ++i)
		{
			UHeroUpgradeBase* NewUpgrade = NewObject<UHeroUpgradeBase>(HeroUpgrades[IndexesToUse[i]]);
			if (IsValid(NewUpgrade))
			{
				MPS->AvailableHeroUpgrades.Add(NewUpgrade);
			}
		}
	}
}

int APlayerManager::GetUpgradePoints(APlayerController* Player) const
{
	if (AMainGamePlayerState* MPS = Player->GetPlayerState<AMainGamePlayerState>())
	{
		return MPS->GetUpgradePoints();
	}

	UE_LOG(LogTemp, Warning, TEXT("%S%u : PlayerState Casting Error Occured."), __FUNCTION__, __LINE__);
	return 0;
}

void APlayerManager::SetHeroUpgradesFromTable()
{
	HeroUpgrades.Empty();
	TArray<FHeroUpgradeRow*> HeroUpgradeRows;
	HeroUpgradesTable->GetAllRows(TEXT("GenerateAvailableUpgradesForPlayer_Implementation"), HeroUpgradeRows);

	for (FHeroUpgradeRow* pRow : HeroUpgradeRows)
	{
		HeroUpgrades.Add(pRow->HeroUpgradeClass);
	}
}

void APlayerManager::Server_AddUpgradePoints_Implementation(APlayerController* Player, int PointsToAdd)
{
	if (AMainGamePlayerState* MPS = Player->GetPlayerState<AMainGamePlayerState>())
	{
		MPS->AddUpgradePoints(PointsToAdd);
	}

	UE_LOG(LogTemp, Warning, TEXT("%S%u : PlayerState Casting Error Occured."), __FUNCTION__, __LINE__);
}

void APlayerManager::Server_SetUpgradePoints_Implementation(APlayerController* Player, int PointsToSet)
{
	if (AMainGamePlayerState* MPS = Player->GetPlayerState<AMainGamePlayerState>())
	{
		MPS->SetUpgradePoints(PointsToSet);
	}

	UE_LOG(LogTemp, Warning, TEXT("%S%u : PlayerState Casting Error Occured."), __FUNCTION__, __LINE__);
}

