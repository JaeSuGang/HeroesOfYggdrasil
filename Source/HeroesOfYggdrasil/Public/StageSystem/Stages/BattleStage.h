// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "StageSystem/StageBase.h"
#include "Data/YggStructData.h"
#include "BattleStage.generated.h"

struct FMonsterDataRow;

class AEnemyManager;

USTRUCT()
struct HEROESOFYGGDRASIL_API FMonsterSpawnInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FDataTableRowHandle MonsterData;

	UPROPERTY(EditAnywhere)
	FVector SpawnLocation;

	UPROPERTY(EditAnywhere)
	float SpawnDelay;

	UPROPERTY(EditAnywhere)
	int Count;
};

USTRUCT()
struct HEROESOFYGGDRASIL_API FWaveTableRow : public FTableRowBase
{
	GENERATED_BODY()
		
	UPROPERTY(EditAnywhere)
	TArray<FMonsterSpawnInfo> SpawnInfos;
};

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UBattleStage : public UStageBase
{
	GENERATED_BODY()
	
public:
	UBattleStage();

public:
	virtual void BeginPlay(UStageSystem* NewStageSystem) override;

	virtual void TickLogic(float DeltaTime) override;

public:
	UFUNCTION()
	void SpawnWave();

	UFUNCTION()
	void LoadTables();

	virtual void Local_OnExitStage(int CurrentRound) override;

	virtual void Local_OnEnterStage(int NewRound) override;

public:
	UFUNCTION()
	void Local_OnEnemyCountChanged(AEnemyManager* EnemyManager);

public:
	UPROPERTY(EditAnywhere)
	UDataTable* WaveTable;

	UPROPERTY(EditAnywhere)
	bool HasEverSpawnedMonster;
	
	TArray<FWaveTableRow*> WaveTableAsArray;
};
