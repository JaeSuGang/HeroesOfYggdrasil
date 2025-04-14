// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/PlayerManager.h"

#include "Math/UnrealMathUtility.h"
#include "Algo/RandomShuffle.h"

#include "MainGame/MainGameState.h"
#include "MainGame/MainGamePlayerState.h"
#include "Player/YggHero.h"
#include "Attribute/HeroAttributeComponent.h"

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

