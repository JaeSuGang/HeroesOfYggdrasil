// Coded By AssortRock Unreal Engine Class Project


#include "SpawningPool/SpawnerManager.h"

// Sets default values
ASpawnerManager::ASpawnerManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Data/StageEnemyDataTable.StageEnemyDataTable'");
	ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

	if (DataTable.Succeeded())
	{
		SpawnDatas = DataTable.Object;
	}
}

// Called when the game starts or when spawned
void ASpawnerManager::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnerManager::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ASpawnerManager::StageEnemySpawn(int32 _Stage)
{
	FString Name = TEXT("Stage_");
	Name.AppendInt(_Stage);
	TArray<FSpawnPortalData>& RowDatas = SpawnDatas->FindRow<FStageEnemyData>(FName(*Name), nullptr)->EnemyDatas;

	for (int32 i = 0; i < RowDatas.Num(); ++i)
	{
		AEnemySpawner* NewSpawner = GetWorld()->SpawnActor<AEnemySpawner>(AEnemySpawner::StaticClass());

		NewSpawner->SetActorLocation(RowDatas[i].SpawnLocation);

		NewSpawner->OnceSpawnCount = RowDatas[i].OnceSpawnCount;
		NewSpawner->MaxSpawnCount = RowDatas[i].MaxSpawnCount;

		NewSpawner->SpawnRange = RowDatas[i].SpawnRange;
		NewSpawner->SpawningActor = RowDatas[i].SpawnEnemy;
		NewSpawner->SpawnDaley = RowDatas[i].SpawnDaley;

		NewSpawner->SpawnStart();
	}
}

