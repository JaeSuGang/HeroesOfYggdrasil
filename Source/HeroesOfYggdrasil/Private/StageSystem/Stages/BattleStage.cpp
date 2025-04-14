#include "StageSystem/Stages/BattleStage.h"

#include "StageSystem/StageSystem.h"
#include "MainGame/EnemyManager.h"


void UBattleStage::BeginPlay(UStageSystem* NewStageSystem)
{
	Super::BeginPlay(NewStageSystem);

	if (StageSystem->GetOwner()->HasAuthority())
	{
		OnEnterStageInternal.AddDynamic(this, &UBattleStage::SpawnWave);
	}
}

void UBattleStage::SpawnWave(FOnEnterStageParams OnEnterStageParams)
{
	LoadTables();

	if (OnEnterStageParams.NewRound < WaveTableAsArray.Num())
	{
		TArray<FMonsterSpawnInfo>& SpawnInfos = WaveTableAsArray[OnEnterStageParams.NewRound]->SpawnInfos;
		if (AEnemyManager* EnemyManager = AEnemyManager::Get(GameState->GetWorld()))
		{
			for (FMonsterSpawnInfo& SpawnInfo : SpawnInfos)
			{
				for (int i = 0; i < SpawnInfo.Count; ++i)
				{
					EnemyManager->CreateMonster(SpawnInfo.MonsterData.RowName.ToString(), SpawnInfo.SpawnLocation);
				}
			}
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%S%u : Failed To Get EnemyManager"), __FUNCTION__, __LINE__);
		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%S%u : Not Enough Waves Are Not Made"), __FUNCTION__, __LINE__);
	}
}

void UBattleStage::LoadTables()
{
	if (WaveTableAsArray.Num() == 0)
	{
		WaveTable->GetAllRows<FWaveTableRow>(TEXT(""), WaveTableAsArray);
	}
}
