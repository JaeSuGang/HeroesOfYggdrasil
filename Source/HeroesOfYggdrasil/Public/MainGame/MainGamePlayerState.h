// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Core/YggPlayerState.h"
#include "MainGamePlayerState.generated.h"

class APlayerSelectZone;
class UHeroUpgradeBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpgradePointsChangedDelegate, int, newType);

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
	void AddUpgradePoints(int PointsToAdd);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SetUpgradePoints(int NewPoints);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSetPlayerName(const FString& name);

public:
	UFUNCTION(BlueprintCallable)
	int GetUpgradePoints() const;

public:
	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FOnUpgradePointsChangedDelegate ClientDelegate_OnUpgradePointsChanged;

	UPROPERTY(VisibleInstanceOnly, Replicated)
	TArray<FPrimaryAssetId> AvailableUpgradeIds;

protected:
	UPROPERTY(Replicated)
	int UpgradePoints;
};
