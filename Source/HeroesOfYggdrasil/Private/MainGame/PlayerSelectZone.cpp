// Coded By AssortRock Unreal Engine Class Project

#include "MainGame/PlayerSelectZone.h"

#include "Net/UnrealNetwork.h"
#include "Data/Playables.h"


APlayerSelectZone::APlayerSelectZone()
{
	bReplicates = true;

	CurrentTableIndex = 0;
}

void APlayerSelectZone::BeginPlay()
{
	Super::BeginPlay();

	if (HasAuthority())
	{
		TArray<FPlayableCharacterRow*> Rows;
		SelectablesTable->GetAllRows(TEXT("GetAllRows"), Rows);
		FActorSpawnParameters SpawnParams{};
		SpawnParams.Owner = nullptr;
		// GetWorld()->SpawnActor(Rows[0]->PlayPawn, GetActorLocation(), FRotator::ZeroRotator, SpawnParams);
	}
}

void APlayerSelectZone::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

void APlayerSelectZone::ServerNextSelectable_Implementation()
{
	/* 미구현 */
}
