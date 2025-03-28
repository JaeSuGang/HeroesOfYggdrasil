// Coded By AssortRock Unreal Engine Class Project


#include "Core/YggPlayerState.h"

#include "Net/UnrealNetwork.h"

void AYggPlayerState::ServerSetPlayerName_Implementation(const FString& name)
{
	APlayerState::SetPlayerName(name);

}

AYggPlayerState::AYggPlayerState()
{
	bUseCustomPlayerNames = true;
}

void AYggPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AYggPlayerState, UpgradePoints);
}

int AYggPlayerState::GetUpgradePoints() const
{
	return UpgradePoints;
}

void AYggPlayerState::SetUpgradePoints_Implementation(int NewPoints)
{
	UpgradePoints = NewPoints;
	ClientDelegate_OnUpgradePointsChanged.Broadcast(UpgradePoints);
}

void AYggPlayerState::AddUpgradePoints_Implementation(int PointsToAdd)
{
	UpgradePoints += PointsToAdd;
	ClientDelegate_OnUpgradePointsChanged.Broadcast(UpgradePoints);
}
