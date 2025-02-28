// Coded By AssortRock Unreal Engine Class Project


#include "SpawningPool/EnemySpawner.h"
#include <Math/UnrealMathUtility.h>

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AEnemySpawner::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AEnemySpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemySpawner::SpawnStart(UClass* _SpawningActor, double _SpawnDaley, FVector _SpawnRange, TFunction<void()> _SpawnStartFunc, TFunction<void()> _SpawnCallFunc)
{
	SpawningActor = _SpawningActor;
	SpawnRange = _SpawnRange;
	SpawnStartFunc = _SpawnStartFunc;
	SpawnCallFunc = _SpawnCallFunc;

	if (SpawnStartFunc != nullptr)
		SpawnStartFunc();

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemySpawner::SpawningCall, _SpawnDaley, true);
}

void AEnemySpawner::SpawningCall()
{
	if (SpawnCallFunc != nullptr)
		SpawnCallFunc();

	FVector Range = FVector::ZeroVector;

	if (SpawnRange != FVector::ZeroVector)
	{
		double X = FMath::FRandRange(0., SpawnRange.X);
		double Y = FMath::FRandRange(0., SpawnRange.Y);
		double Z = FMath::FRandRange(0., SpawnRange.Z);

		Range = FVector(X, Y, Z) - (SpawnRange / 2.);
	}

	for (int i = 0; i < OnceSpawnCount; ++i)
	{
		FVector Location = GetActorLocation();
		AActor* NewActor = GetWorld()->SpawnActor(SpawningActor);
		NewActor->SetActorLocation(Location + Range);
		++CurrentSpawnCount;

		if (CurrentSpawnCount >= MaxSpawnCount)
		{
			GetWorldTimerManager().ClearTimer(TimerHandle);
			CurrentSpawnCount = 0;
			break;
		}
	}
}
