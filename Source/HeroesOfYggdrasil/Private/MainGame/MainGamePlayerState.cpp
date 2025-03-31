// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/MainGamePlayerState.h"

#include "Net/UnrealNetwork.h"

#include "Upgrade/Upgrades.h"

void AMainGamePlayerState::ServerSetPlayerName_Implementation(const FString& name)
{
	AMainGamePlayerState::SetPlayerName(name);

}

void AMainGamePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainGamePlayerState, UpgradePoints);
}

int AMainGamePlayerState::GetUpgradePoints() const
{
	return UpgradePoints;
}

UHeroUpgradeBase* AMainGamePlayerState::InstantiateHeroUpgrade(TSubclassOf<UHeroUpgradeBase> NewHeroUpgradeClass)
{
	return NewObject<UHeroUpgradeBase>(NewHeroUpgradeClass);
}

void AMainGamePlayerState::SetUpgradePoints_Implementation(int NewPoints)
{
	UpgradePoints = NewPoints;
	ClientDelegate_OnUpgradePointsChanged.Broadcast(UpgradePoints);
}

void AMainGamePlayerState::AddUpgradePoints_Implementation(int PointsToAdd)
{
	UpgradePoints += PointsToAdd;
	ClientDelegate_OnUpgradePointsChanged.Broadcast(UpgradePoints);
}
