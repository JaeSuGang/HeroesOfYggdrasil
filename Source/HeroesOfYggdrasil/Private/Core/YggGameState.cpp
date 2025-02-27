// Coded By AssortRock Unreal Engine Class Project


#include "Core/YggGameState.h"

#include "Net/UnrealNetwork.h"

AYggGameState::AYggGameState(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{

}

void AYggGameState::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		this->InitPlayerManager();
		this->InitStageManager(nullptr);
	}
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

void AYggGameState::InitStageManager(TSubclassOf<AStageManager> _Test)
{
	if (HasAuthority())
	{
		StageManagerClass;

		StageManager = GetWorld()->SpawnActor<AStageManager>(StageManagerClass);
	}
}

AStageManager* AYggGameState::GetStageManager() const
{
	return StageManager;
}
