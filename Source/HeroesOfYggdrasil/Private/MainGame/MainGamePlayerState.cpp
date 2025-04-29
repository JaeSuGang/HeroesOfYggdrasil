// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/MainGamePlayerState.h"

#include "Net/UnrealNetwork.h"

#include "UpgradeSystem/UpgradeSystem.h"


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

void AMainGamePlayerState::Request_Upgrade_Implementation(UAttributeComponent* AttributeComponent, FPrimaryAssetId AssetId)
{
	ensure(HasAuthority());

	if (UUpgradeSystem* UpgradeSystem = UUpgradeSystem::Get(this))
	{
		GEngine->AssetManager->LoadPrimaryAsset(AssetId, TArray<FName>(), FStreamableDelegate::CreateLambda([this, UpgradeSystem, AttributeComponent, AssetId]()
			{
				if (UObject* LoadedObject = GEngine->AssetManager->GetPrimaryAssetObject(AssetId))
				{
					if (UUpgradeDataAsset* UpgradeDataAsset = Cast<UUpgradeDataAsset>(LoadedObject))
					{
						UpgradeSystem->UpgradeInternal(AttributeComponent, UpgradeDataAsset);
					}
					else
					{
						UE_LOG(LogTemp, Warning, TEXT("%S%u : Cast Failed"), __FUNCTION__, __LINE__);
					}
				}
				else
				{
					UE_LOG(LogTemp, Warning, TEXT("%S%u : Invalid Asset"), __FUNCTION__, __LINE__);
				}
			}));

	}
}


void AMainGamePlayerState::OnRep_UpgradePoints()
{
	FOnUpgradePointsChangedParams OnUpgradePointsChangedParams{};
	OnUpgradePointsChangedParams.NewUpgradePoints = UpgradePoints;
	OnUpgradePointsChanged.Broadcast(OnUpgradePointsChangedParams);
}
