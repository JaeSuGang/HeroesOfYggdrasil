#include "StageSystem/Stages/BattleStage.h"

#include "StageSystem/StageSystem.h"
#include "MainGame/EnemyManager.h"


UBattleStage::UBattleStage()
{
	bIsUsingTimer = false;
}

void UBattleStage::BeginPlay(UStageSystem* NewStageSystem)
{
	Super::BeginPlay(NewStageSystem);

	if (StageSystem->GetOwner()->HasAuthority())
	{
		OnEnterStageInternal.AddDynamic(this, &UBattleStage::SpawnWave);
	}
}

void UBattleStage::TickLogic(float DeltaTime)
{
	Super::TickLogic(DeltaTime);


}

void UBattleStage::SpawnWave(FOnEnterStageParams OnEnterStageParams)
{
	LoadTables();

	if (OnEnterStageParams.NewRound < WaveTableAsArray.Num() && OnEnterStageParams.NewRound > 0)
	{
		TArray<FMonsterSpawnInfo>& SpawnInfos = WaveTableAsArray[OnEnterStageParams.NewRound - 1]->SpawnInfos;
		if (AEnemyManager* EnemyManager = AEnemyManager::Get(StageSystem->GetOwner()->GetWorld()))
		{
			for (FMonsterSpawnInfo& SpawnInfo : SpawnInfos)
			{
				for (int i = 0; i < SpawnInfo.Count; ++i)
				{
					FTimerHandle TH{};
					StageSystem->GetWorld()->GetTimerManager().SetTimer(TH, [EnemyManager, SpawnInfo]() {EnemyManager->CreateMonster(SpawnInfo.MonsterData.RowName.ToString(), SpawnInfo.SpawnLocation); }, (float)i + SpawnInfo.SpawnDelay, false);
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
