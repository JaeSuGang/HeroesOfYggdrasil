// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/StageManager.h"

#include "Kismet/GameplayStatics.h"

#include "MainGame/MainGameState.h"
#include "MainGame/MainGameHUD.h"

AStageManager* AStageManager::Get(UWorld* WorldContext)
{
	AMainGameState* MGS = WorldContext->GetGameState<AMainGameState>();
	if (MGS)
	{
		return MGS->GetStageManager();
	}

	return nullptr;
}

AStageManager::AStageManager(const FObjectInitializer& ObjectInitializer)
	:
	Super(ObjectInitializer)
{
	bReplicates = true;
	bAlwaysRelevant = true;
	NetDormancy = DORM_Never;

	Round = 0;
}

void AStageManager::OnEnterReadyFinishedGameState_Implementation()
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(GetWorld(), 0))
	{
		if (AMainGameHUD* MGH = Cast<AMainGameHUD>(PC->GetHUD()))
		{
			MGH->CloseCurrentWidget();
			MGH->ShowMainGameWidget();
		}
	}
}