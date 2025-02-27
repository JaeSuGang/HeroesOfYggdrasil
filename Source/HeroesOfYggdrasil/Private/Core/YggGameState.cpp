// Coded By AssortRock Unreal Engine Class Project


#include "Core/YggGameState.h"

#include "Net/UnrealNetwork.h"

void AYggGameState::BeginPlay()
{
	Super::BeginPlay();

	this->InitPlayerManager();
	this->InitStageManager();
}

void AYggGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AYggGameState, PlayerManager);
	DOREPLIFETIME(AYggGameState, StageManager);
}

void AYggGameState::InitPlayerManager()
{
	if (HasAuthority())
	{
		PlayerManager = GetWorld()->SpawnActor<APlayerManager>(PlayerManagerClass);
	}
}

APlayerManager* AYggGameState::GetPlayerManager() const
{
	return PlayerManager;
}

void AYggGameState::InitStageManager()
{
	if (HasAuthority())
	{
		StageManager = GetWorld()->SpawnActor<AStageManager>(StageManagerClass);
	}
}

AStageManager* AYggGameState::GetStageManager() const
{
	return StageManager;
}
