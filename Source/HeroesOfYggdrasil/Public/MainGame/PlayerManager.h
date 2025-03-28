// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "MainGame/MainGamePlayerState.h"
#include "PlayerManager.generated.h"

class UWorld;
class AMainGamePlayerState;
class APlayerController;
class UDataTable;


#define CHARACTER_UPGRADE_INFO_ROW_ATTACK TEXT("Attack")
#define CHARACTER_UPGRADE_INFO_ROW_DEFENSE TEXT("Defense")
#define CHARACTER_UPGRADE_INFO_ROW_HEALTH TEXT("HP")
#define CHARACTER_UPGRADE_INFO_ROW_MOVE_SPEED TEXT("MaxMoveSpeed")
#define CHARACTER_UPGRADE_INFO_ROW_ATTACK_SPEED TEXT("AttackSpeedRate")

USTRUCT(BlueprintType)
struct HEROESOFYGGDRASIL_API FCharacterUpgradeInfoRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float ValueIncrementPerUpgrade;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int MaxUpgrade;
};

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

public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_UpgradeAttack(APlayerController* PC);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_UpgradeDefense(APlayerController* PC);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_UpgradeHealth(APlayerController* PC);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_UpgradeMoveSpeed(APlayerController* PC);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_UpgradeAttackSpeed(APlayerController* PC);

	UFUNCTION(BlueprintCallable)
	int GetUpgradePoints(APlayerController* Player) const;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_AddUpgradePoints(APlayerController* Player, int PointsToAdd);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SetUpgradePoints(APlayerController* Player, int PointsToSet);

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (RowType = "FCharacterUpgradeInfoRow"))
	UDataTable* UpgradeTable;

protected:


};
