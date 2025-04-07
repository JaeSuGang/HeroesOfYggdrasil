// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/MainGameState.h"

#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

#include "MainGame/UI/MainGameHUD.h"
#include "MainGame/PlayerManager.h"
#include "StageSystem/StageManager.h"
#include "StageSystem/StageSystem.h"
#include "UpgradeSystem/UpgradeSystem.h"


AMainGameState::AMainGameState()
{
	StageSystem = CreateDefaultSubobject<UStageSystem>(TEXT("StageSystem"));

	UpgradeSystem = CreateDefaultSubobject<UUpgradeSystem>(TEXT("UpgradeSystem"));
}

void AMainGameState::BeginPlay()
{
	Super::BeginPlay();

}

void AMainGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainGameState, StageSystem);
	DOREPLIFETIME(AMainGameState, UpgradeSystem);

	DOREPLIFETIME(AMainGameState, PlayerManager);
	DOREPLIFETIME(AMainGameState, StageManager);
	DOREPLIFETIME(AMainGameState, EnemyManager);
	DOREPLIFETIME(AMainGameState, UpgradeManager);
}

APlayerManager* AMainGameState::GetPlayerManager() const
{
	return PlayerManager;
}

AEnemyManager* AMainGameState::GetEnemyManager() const
{
	return EnemyManager;
}

AStageManager* AMainGameState::GetStageManager() const
{
	return StageManager;
}