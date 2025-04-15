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