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
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		SpawnedSelectable = GetWorld()->SpawnActor<APawn>(Rows[0]->PlayPawn, GetActorLocation(), GetActorRotation(), SpawnParams);
	}
}

void APlayerSelectZone::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

void APlayerSelectZone::ServerSelectCharacter_Implementation(APlayerController* PC)
{
	if (HasAuthority())
	{
		PC->UnPossess();
		PC->Possess(SpawnedSelectable);
	}
}

void APlayerSelectZone::ServerNextSelectable_Implementation()
{
	/* 미구현 */
}
