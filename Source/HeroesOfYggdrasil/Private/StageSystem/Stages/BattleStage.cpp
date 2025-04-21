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
		OnEnterStageDelegate.AddDynamic(this, &UBattleStage::SpawnWave);
	}
}

void UBattleStage::TickLogic(float DeltaTime)
{
	Super::TickLogic(DeltaTime);

	if (AEnemyManager* EM = AEnemyManager::Get(StageSystem->GetWorld()))
	{
		if (HasEverSpawnedMonster && EM->AllEnemyCharacter.Num() <= 0)
		{
			EnterNextStage();
		}
	}
}

void UBattleStage::SpawnWave(FOnEnterStageDelegateParams OnEnterStageParams)
{
	LoadTables();

	if (OnEnterStageParams.NewRound < WaveTableAsArray.Num() + 1 && OnEnterStageParams.NewRound > 0)
	{
		TArray<FMonsterSpawnInfo>& SpawnInfos = WaveTableAsArray[OnEnterStageParams.NewRound - 1]->SpawnInfos;
		if (AEnemyManager* EnemyManager = AEnemyManager::Get(StageSystem->GetOwner()->GetWorld()))
		{
			for (FMonsterSpawnInfo& SpawnInfo : SpawnInfos)
			{
				for (int i = 0; i < SpawnInfo.Count; ++i)
				{
					// EnemyManager->CreateMonster(SpawnInfo.MonsterData.RowName.ToString(), SpawnInfo.SpawnLocation);
					int ab = i;
					FTimerHandle TH{};
					StageSystem->GetWorld()->GetTimerManager().SetTimer(TH, [this, EnemyManager, SpawnInfo, ab]() { HasEverSpawnedMonster = true; EnemyManager->CreateMonster(SpawnInfo.MonsterData.RowName.ToString(), SpawnInfo.SpawnLocation); }, (float)i + SpawnInfo.SpawnDelay, false);
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

void UBattleStage::Local_OnExitStage(int CurrentRound)
{
	Super::Local_OnExitStage(CurrentRound);
}

void UBattleStage::Local_OnEnterStage(int NewRound)
{
	Super::Local_OnEnterStage(NewRound);

	HasEverSpawnedMonster = false;
}
