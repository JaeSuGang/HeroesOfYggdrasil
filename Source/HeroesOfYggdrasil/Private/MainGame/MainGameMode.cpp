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
#include "MainGame/EnemyManager.h"
#include "Upgrade/UpgradeManager.h"

void AMainGameMode::InitGameState()
{
	Super::InitGameState();

	/* Initialize Avaliable Player IDs */
	for (int i = 0; i < 4; ++i)
		AvailablePlayerIds.HeapPush(i);

	/* MainGameState Cast */
	AMainGameState* MGS = GetGameState<AMainGameState>();
	if (!MGS)
	{
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) MainGameState has not been initialized"), __FUNCTION__, __LINE__);
		return;
	}

	/* Manager Initialization */
	MGS->PlayerManager = GetWorld()->SpawnActor<APlayerManager>(MGS->PlayerManagerClass);
	MGS->StageManager = GetWorld()->SpawnActor<AStageManager>(MGS->StageManagerClass);
	MGS->EnemyManager = GetWorld()->SpawnActor<AEnemyManager>(MGS->EnemyManagerClass);
	MGS->UpgradeManager = GetWorld()->SpawnActor<AUpgradeManager>(AUpgradeManager::StaticClass());
}

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void AMainGameMode::PostLogin(APlayerController* PC)
{
	if (AYggPlayerState* YPS = PC->GetPlayerState<AYggPlayerState>())
	{
		int nPlayerId = 0;
		AvailablePlayerIds.HeapPop(nPlayerId);
		YPS->SetPlayerId(nPlayerId);
	}

	Super::PostLogin(PC);


}

void AMainGameMode::Logout(AController* controller)
{
	Super::Logout(controller);

	if (AYggPlayerController* YPC = Cast<AYggPlayerController>(controller))
	{
		if (AYggPlayerState* YPS = YPC->GetPlayerState<AYggPlayerState>())
		{
			AvailablePlayerIds.HeapPush(YPS->GetPlayerId());
		}

		if (YPC->GetPawn())
		{
			YPC->GetPawn()->Destroy();
		}
	}
}


