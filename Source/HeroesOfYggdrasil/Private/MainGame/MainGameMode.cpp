	// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/MainGameMode.h"

#include "Algo/Heapify.h"
#include "Kismet/GameplayStatics.h"

#include "Core/YggGameState.h"
#include "Core/YggPlayerController.h"
#include "MainGame/MainGameState.h"
#include "MainGame/MainGamePlayerState.h"
#include "MainGame/PlayerSelectZone.h"
#include "MainGame/StageManager.h"
#include "MainGame/PlayerManager.h"

void AMainGameMode::InitGameState()
{
	Super::InitGameState();

	/* Initialize Avaliable Player IDs */
	Algo::Heap
	AvailablePlayerIds.

	/* MainGameState Cast */
	AMainGameState* MGS = GetGameState<AMainGameState>();
	if (!MGS)
	{
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) MainGameState has not been initialized"), __FUNCTION__, __LINE__);
		return;
	}

	/* Manager Initialization */
	MGS->PlayerManager = GetWorld()->SpawnActor<APlayerManager>();
	MGS->StageManager = GetWorld()->SpawnActor<AStageManager>();
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void AMainGameMode::PostLogin(APlayerController* PC)
{
	Super::PostLogin(PC);

	if (AYggPlayerState* YPS = PC->GetPlayerState<AYggPlayerState>())
	{
		Ava
		YPS->SetPlayerId()
	}
}

void AMainGameMode::Logout(AController* controller)
{
	Super::Logout(controller);
}


