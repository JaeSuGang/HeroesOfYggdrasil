// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/MainGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#include "MainGame/MainGameHUD.h"
#include "MainGame/PlayerManager.h"
#include "MainGame/StageManager.h"



void AMainGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		this->InitPlayerManager();
		this->InitStageManager();
	}
}

void AMainGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainGameState, PlayerManager);
	DOREPLIFETIME(AMainGameState, StageManager);
}

void AMainGameState::InitPlayerManager()
{
	if (HasAuthority())
	{
		PlayerManager = GetWorld()->SpawnActor<APlayerManager>(PlayerManagerClass);
	}
}

APlayerManager* AMainGameState::GetPlayerManager() const
{
	return PlayerManager;
}

void AMainGameState::InitStageManager()
{
	if (HasAuthority())
	{
		StageManagerClass;

		StageManager = GetWorld()->SpawnActor<AStageManager>(StageManagerClass);
	}
}

AStageManager* AMainGameState::GetStageManager() const
{
	return StageManager;
}