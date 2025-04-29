// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Core/YggPlayerState.h"
#include "MainGamePlayerState.generated.h"

class APlayerSelectZone;
class UHeroUpgradeBase;
class UAttributeComponent;

USTRUCT()
struct FOnUpgradePointsChangedParams
{
	GENERATED_BODY()

	UPROPERTY()
	int NewUpgradePoints;
};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpgradePointsChanged, FOnUpgradePointsChangedParams, OnUpgradePointsChangedParams);

/**
 * 담당 코더 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API AMainGamePlayerState : public AYggPlayerState
{
	GENERATED_BODY()
	
protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Request_Upgrade(UAttributeComponent* AttributeComponent, FPrimaryAssetId AssetId);
	void Request_Upgrade_Implementation(UAttributeComponent* AttributeComponent, FPrimaryAssetId AssetId);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSetPlayerName(const FString& name);

	UFUNCTION()
	void OnRep_UpgradePoints();

public:
	UPROPERTY()
	FOnUpgradePointsChanged OnUpgradePointsChanged;

public:
	UPROPERTY(Replicated, VisibleInstanceOnly)
	TArray<FPrimaryAssetId> AvailableUpgradeIds;

	UPROPERTY(ReplicatedUsing=OnRep_UpgradePoints, VisibleInstanceOnly)
	int UpgradePoints;
};
