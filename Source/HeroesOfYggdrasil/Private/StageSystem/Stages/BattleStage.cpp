// Coded By AssortRock Unreal Engine Class Project


#include "StageSystem/Stages/BattleStage.h"

void UBattleStage::SpawnWave(int nRound)
{
	LoadTables();

	if (nRound < WaveTableAsArray.Num())
	{
		TArray<FMonsterSpawnInfo>& SpawnInfos = WaveTableAsArray[nRound]->SpawnInfos;
		for (FMonsterSpawnInfo& SpawnInfo : SpawnInfos)
		{
			// SpawnInfo.MonsterData.AIData.EnemyName
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
