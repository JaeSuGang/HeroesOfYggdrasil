// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "MainGame/MainGamePlayerState.h"
#include "PlayerManager.generated.h"

class UWorld;
class UDataTable;
class UHeroUpgradeBase;
class AMainGamePlayerState;
class APlayerController;


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

USTRUCT(BlueprintType)
struct HEROESOFYGGDRASIL_API FHeroUpgradeRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<UHeroUpgradeBase> HeroUpgradeClass;
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

protected:
	void BeginPlay() override;

public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SelectUpgrade(APlayerController* PC, int nChoiceIndex);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_GenerateAvailableUpgradesForPlayer(APlayerController* PC, int nChoices);

	UFUNCTION(BlueprintCallable)
	int GetUpgradePoints(APlayerController* Player) const;

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_AddUpgradePoints(APlayerController* Player, int PointsToAdd);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void Server_SetUpgradePoints(APlayerController* Player, int PointsToSet);

protected:
	void SetHeroUpgradesFromTable();

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (RowType = "FHeroUpgradeRow"))
	UDataTable* HeroUpgradesTable;

protected:
	UPROPERTY()
	TArray<TSubclassOf<UHeroUpgradeBase>> HeroUpgrades;

};
