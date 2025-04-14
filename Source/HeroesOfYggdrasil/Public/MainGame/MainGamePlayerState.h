// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Core/YggPlayerState.h"
#include "MainGamePlayerState.generated.h"

class APlayerSelectZone;
class UHeroUpgradeBase;

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
	void ServerSetPlayerName(const FString& name);

public:
	UPROPERTY(Replicated, VisibleInstanceOnly)
	TArray<FPrimaryAssetId> AvailableUpgradeIds;

	UPROPERTY(Replicated)
	int UpgradePoints;
};
