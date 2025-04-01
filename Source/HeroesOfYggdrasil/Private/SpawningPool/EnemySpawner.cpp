// Coded By AssortRock Unreal Engine Class Project


#include "SpawningPool/EnemySpawner.h"
#include <Components/SceneComponent.h>
#include <MainGame/MainGameState.h>
#include <MainGame/EnemyManager.h>
#include <Math/UnrealMathUtility.h>

// Sets default values
AEnemySpawner::AEnemySpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	RootComponent = CreateDefaultSubobject<USceneComponent>("Root");

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

void AEnemySpawner::SpawnStart()
{
	if (Invalid == true)
		return;

	Invalid = true;
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AEnemySpawner::SpawningCall, SpawnDaley, true);
}

void AEnemySpawner::OnceSpawningCall_Implementation(const FString& _SpawnMonsterName, int32 _Count, double _Delay)
{
	OnceSpawnCount = 1;
	MaxSpawnCount = _Count;
	SpawnMonsterName = _SpawnMonsterName;
	SpawnDaley = _Delay;

	SpawnStart();
}

void AEnemySpawner::SpawningCall()
{
	AMainGameState* GameState = Cast<AMainGameState>(GetWorld()->GetGameState());
	if (!GameState)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		Destroy();
		return;
	}

	AEnemyManager* EnemyManager = GameState->GetEnemyManager();
	if (!EnemyManager)
	{
		GetWorldTimerManager().ClearTimer(TimerHandle);
		Destroy();
		return;
	}

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
		EnemyManager->CreateMonster(SpawnMonsterName, Location + Range);
		++CurrentSpawnCount;

		if (CurrentSpawnCount >= MaxSpawnCount)
		{
			GetWorldTimerManager().ClearTimer(TimerHandle);
			Destroy();
			break;
		}
	}
}
