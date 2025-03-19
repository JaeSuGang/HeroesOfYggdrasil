// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/StageManager.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#include "MainGame/GameStage.h"
#include "MainGame/MainGameState.h"
#include "MainGame/UI/MainGameHUD.h"
#include "MainGame/PlayerSelectZone.h"

AStageManager* AStageManager::Get(UWorld* WorldContext)
{
	AMainGameState* MGS = WorldContext->GetGameState<AMainGameState>();
	if (MGS)
	{
		return MGS->GetStageManager();
	}

	return nullptr;
}

void AStageManager::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		EnterStage(FirstStageToStart);
	}
}

void AStageManager::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AStageManager, Round);
}

void AStageManager::EnterStage_Implementation(TSubclassOf<AGameStage> stage)
{
	int nRound = 0;
	if (CurrentStage)
	{
		nRound = CurrentStage->Round;
		CurrentStage->Destroy();
	}

	CurrentStage = GetWorld()->SpawnActor<AGameStage>(stage);
	CurrentStage->Round = nRound;
}

void AStageManager::StartGame_Implementation()
{
	auto ControllerIter = GetWorld()->GetPlayerControllerIterator();
	while (ControllerIter)
	{
		APlayerController* PC = ControllerIter->Get();
		if (APlayerSelectZone* PSZ = Cast<APlayerSelectZone>(PC->GetPawn()))	
		{
			PSZ->SelectCharacter();
		}
		++ControllerIter;
	}

	CurrentStage->EnterNextStage();

	ForceMainWidgetToClients();
}

void AStageManager::ForceMainWidgetToClients_Implementation()
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

AStageManager::AStageManager(const FObjectInitializer& ObjectInitializer)
	:
	Super(ObjectInitializer)
{
	bReplicates = true;
	bAlwaysRelevant = true;
	NetDormancy = DORM_Never;
	Round = 0;
}

