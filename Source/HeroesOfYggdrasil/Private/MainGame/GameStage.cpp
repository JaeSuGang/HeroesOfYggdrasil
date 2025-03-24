// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/GameStage.h"

#include "Net/UnrealNetwork.h"

#include "MainGame/StageManager.h"
#include "MainGame/EnemyManager.h"
#include "SpawningPool/EnemySpawner.h"

AGameStage::AGameStage()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	bAlwaysRelevant = true;
	NetDormancy = DORM_Never;
}

void AGameStage::Tick(float fDeltaTime)
{
	Super::Tick(fDeltaTime);

	if (bIsTimerEnabled)
	{
		Timer -= fDeltaTime;
	}

	if (HasAuthority() && ShouldEnterNextStage())
	{
		EnterNextStage();
	}
}

void AGameStage::BeginPlay()
{
	Super::BeginPlay();
	
	if (HasAuthority())
	{
		this->OnEnterStage();
	}
}

void AGameStage::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (EndPlayReason == EEndPlayReason::Type::Destroyed)
	{
		if (HasAuthority())
		{
			this->OnExitStage();
		}
	}
}

void AGameStage::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(AGameStage, Round);
}

void AGameStage::SpawnEnemySpawner(FMonsterDataRow MonsterRow, FVector Location, int nEnemyCount, float fDelay)
{
	FTransform SpawnerTransform{};
	SpawnerTransform.SetLocation(Location);

	AEnemySpawner* EnemySpawner = GetWorld()->SpawnActor<AEnemySpawner>(AEnemySpawner::StaticClass(), SpawnerTransform);
	if (EnemySpawner)
	{
		EnemySpawner->OnceSpawningCall(FString{ MonsterRow.AIData.EnemyName.ToString()}, nEnemyCount, fDelay);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%S%u : Could Not Spawn EnemySpawner"), __FUNCTION__, __LINE__);
	}

}

void AGameStage::EnterNextStage_Implementation()
{
	if (AStageManager* StageManager = AStageManager::Get(GetWorld()))
	{
		if (NextStage)
		{
			StageManager->EnterStage(NextStage);
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%S%u : Could Not Open Next Stage. NextStage is null"), __FUNCTION__, __LINE__);

		}
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("%S%u : Stage Manager is null"), __FUNCTION__, __LINE__);
	}
}

bool AGameStage::ShouldEnterNextStage_Implementation()
{
	return false;
}

void AGameStage::OnExitStage_Implementation()
{

}

void AGameStage::OnEnterStage_Implementation()
{

}
