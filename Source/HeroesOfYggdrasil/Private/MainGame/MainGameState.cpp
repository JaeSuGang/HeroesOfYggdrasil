// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/MainGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#include "MainGame/UI/MainGameHUD.h"
#include "MainGame/PlayerManager.h"
#include "MainGame/StageManager.h"



void AMainGameState::BeginPlay()
{
	Super::BeginPlay();

}

void AMainGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainGameState, PlayerManager);
	DOREPLIFETIME(AMainGameState, StageManager);
}

APlayerManager* AMainGameState::GetPlayerManager() const
{
	return PlayerManager;
}

AStageManager* AMainGameState::GetStageManager() const
{
	return StageManager;
}