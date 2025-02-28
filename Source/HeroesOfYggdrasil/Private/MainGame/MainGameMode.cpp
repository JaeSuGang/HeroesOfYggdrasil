	// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/MainGameMode.h"

#include "Kismet/GameplayStatics.h"

#include "Core/YggGameState.h"
#include "MainGame/MainGameState.h"
#include "MainGame/PlayerSelectZone.h"
#include "MainGame/StageManager.h"

void AMainGameMode::BeginPlay()
{
	Super::BeginPlay();

}

void AMainGameMode::PostLogin(APlayerController* PC)
{
	Super::PostLogin(PC);

	FVector FinalSelectZoneLocation = SelectZoneLocation;
	FinalSelectZoneLocation += SelectZonePosOffset * (GetNumPlayers() - 1);
	FActorSpawnParameters SpawnParams{};
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	APlayerSelectZone* Zone = GetWorld()->SpawnActor<APlayerSelectZone>(SelectZone, FinalSelectZoneLocation, SelectZoneRotation, SpawnParams);
	PlayerZones.Add(Zone);
}

void AMainGameMode::OnAllPlayersReady()
{
	int i = 0;
	for (APlayerSelectZone* PlayerZone : PlayerZones)
	{
		PlayerZone->ServerSelectCharacter(UGameplayStatics::GetPlayerController(GetWorld(), i));
		i++;
	}

	PlayerZones.Empty();

	AStageManager* SM = AStageManager::Get(GetWorld());
	if (SM)
	{
		SM->OnEnterReadyFinishedGameState();
	}
}

