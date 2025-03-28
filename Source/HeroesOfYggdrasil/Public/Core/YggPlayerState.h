// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "YggPlayerState.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnUpgradePointsChangedDelegate, int, newType);

/**
 * 담당 코더 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API AYggPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public:
	AYggPlayerState();

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void AddUpgradePoints(int PointsToAdd);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void SetUpgradePoints(int NewPoints);

	UFUNCTION(BlueprintCallable)
	int GetUpgradePoints() const;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void ServerSetPlayerName(const FString& name);

public:
	UPROPERTY(BlueprintAssignable, BlueprintReadWrite)
	FOnUpgradePointsChangedDelegate ClientDelegate_OnUpgradePointsChanged;

protected:
	UPROPERTY(Replicated)
	int UpgradePoints;
};
