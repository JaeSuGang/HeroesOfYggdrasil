// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "StageSystem/StageBase.h"
#include "Data/YggStructData.h"
#include "BattleStage.generated.h"

struct FMonsterDataRow;

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
	UFUNCTION()
	void SpawnWave(int nRound);

	UFUNCTION()
	void LoadTables();


public:
	UPROPERTY(EditAnywhere)
	UDataTable* WaveTable;

	TArray<FWaveTableRow*> WaveTableAsArray;
};
