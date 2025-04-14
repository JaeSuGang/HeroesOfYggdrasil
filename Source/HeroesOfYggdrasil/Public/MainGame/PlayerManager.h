// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "MainGame/MainGamePlayerState.h"
#include "PlayerManager.generated.h"

class UWorld;
class UDataTable;
class AMainGamePlayerState;
class APlayerController;

/**
 * 담당 코더 : 김경민
 */
UCLASS(Blueprintable)
class HEROESOFYGGDRASIL_API APlayerManager : public AInfo
{
	GENERATED_BODY()
	
public:
	APlayerManager();
	
	UFUNCTION(BlueprintCallable)
	static APlayerManager* Get(UWorld* WorldContext);

	UFUNCTION(BlueprintCallable)
	static AMainGamePlayerState* GetPlayerState(APlayerController* PC);

protected:
	void BeginPlay() override;

public:
	UFUNCTION(BlueprintCallable)
	int GetUpgradePoints(APlayerController* Player) const;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_AddUpgradePoints(APlayerController* Player, int PointsToAdd);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SetUpgradePoints(APlayerController* Player, int PointsToSet);

protected:

};
