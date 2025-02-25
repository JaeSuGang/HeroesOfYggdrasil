	// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/MainGameMode.h"
#include "MainGame/MainGameState.h"

#include "MainGame/PlayerSelectZone.h"
#include "Kismet/GameplayStatics.h"

void AMainGameMode::PostLogin(APlayerController* PC)
{
	Super::PostLogin(PC);

	FVector FinalSelectZoneLocation = SelectZoneLocation;
	FinalSelectZoneLocation += SelectZonePosOffset * (GetNumPlayers() - 1);
	FActorSpawnParameters SpawnParams{};
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	GetWorld()->SpawnActor<AActor>(SelectZone, FinalSelectZoneLocation, SelectZoneRotation, SpawnParams);
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

	if (AMainGameState* MainGameState = Cast<AMainGameState>(GameState))
	{
		MainGameState->OnEnterReadyFinishedGameState();
	}
}
