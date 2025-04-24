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

	LoadTables();

	if (AEnemyManager* EM = AEnemyManager::Get(GetWorld()))
	{
		EM->OnEnemyCountDelegate.AddDynamic(this, &UBattleStage::Local_OnEnemyCountChanged);
	}
}

void UBattleStage::TickLogic(float DeltaTime)
{
	Super::TickLogic(DeltaTime);

}

void UBattleStage::SpawnWave()
{
	LoadTables();

	if (StageSystem->CurrentRound < WaveTableAsArray.Num() + 1 && StageSystem->CurrentRound > 0)
	{
		TArray<FMonsterSpawnInfo>& SpawnInfos = WaveTableAsArray[StageSystem->CurrentRound - 1]->SpawnInfos;
		if (AEnemyManager* EnemyManager = AEnemyManager::Get(StageSystem->GetOwner()->GetWorld()))
		{
			int j = 0;
			for (FMonsterSpawnInfo& SpawnInfo : SpawnInfos)
			{
				for (int i = 0; i < SpawnInfo.Count; ++i)
				{
					// EnemyManager->CreateMonster(SpawnInfo.MonsterData.RowName.ToString(), SpawnInfo.SpawnLocation);
					FTimerHandle TH{};
					StageSystem->GetWorld()->GetTimerManager().SetTimer(TH, [i, j, this, EnemyManager, SpawnInfo]()
						{
							FVector LocationToSpawn = SpawnLocations[(i+j) % SpawnLocations.Num()] + FVector(FMath::FRandRange(-150.0f, 150.0f), FMath::FRandRange(-150.0f, 150.0f), 0.0f);
							HasEverSpawnedMonster = true; EnemyManager->CreateMonster(SpawnInfo.MonsterData.RowName.ToString(), LocationToSpawn);
						},
						(float)((i + j) / SpawnLocations.Num()), false);
				}
				j += SpawnInfo.Count;
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

	if (StageSystem->GetOwner()->HasAuthority())
	{
		SpawnWave();
	}
}

void UBattleStage::Local_OnEnemyCountChanged(AEnemyManager* EnemyManager)
{
	if (StageSystem->StageCycle[StageSystem->CurrentStageIndex] != this)
		return;

	if (StageSystem->GetOwner()->HasAuthority())
	{
		if (EnemyManager->AllEnemyCharacter.Num() <= 0)
		{
			EnterNextStage();
		}
	}
}
