// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/MainGamePlayerState.h"

#include "Net/UnrealNetwork.h"


void AMainGamePlayerState::ServerSetPlayerName_Implementation(const FString& name)
{
	AMainGamePlayerState::SetPlayerName(name);

}

void AMainGamePlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AMainGamePlayerState, UpgradePoints);
	DOREPLIFETIME(AMainGamePlayerState, AvailableUpgradeIds);
}

void AMainGamePlayerState::OnRep_UpgradePoints()
{
	FOnUpgradePointsChangedParams OnUpgradePointsChangedParams{};
	OnUpgradePointsChangedParams.NewUpgradePoints = UpgradePoints;
	OnUpgradePointsChanged.Broadcast(OnUpgradePointsChangedParams);
}
