// Coded By AssortRock Unreal Engine Class Project


#include "SpawningPool/SpawnManagerComponent.h"

// Sets default values for this component's properties
USpawnManagerComponent::USpawnManagerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	FString DataPath = TEXT("/Script/Engine.DataTable'/Game/Data/StageEnemyDataTable.StageEnemyDataTable'");
	ConstructorHelpers::FObjectFinder<UDataTable> DataTable(*DataPath);

	if (DataTable.Succeeded())
	{
		SpawnDatas = DataTable.Object;
	}
}


// Called when the game starts
void USpawnManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void USpawnManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

// don't use
void USpawnManagerComponent::StageEnemySpawn(int32 _Stage)
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
		NewSpawner->SpawnDaley = RowDatas[i].SpawnDaley;

		NewSpawner->SpawnStart();
	}
}

