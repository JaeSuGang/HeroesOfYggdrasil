// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class HEROESOFYGGDRASIL_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	friend class ASpawnerManager;

public:	
	// Sets default values for this actor's properties
	AEnemySpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	void SpawningCall();
	void SpawnStart(UClass* _SpawningActor, double _SpawnDaley, FVector _SpawnRange, TFunction<void()> _SpawnStartFunc, TFunction<void()> _SpawnCallFunc);
	void SetSpawnStartFunc(TFunction<void()> _Function)
	{
		SpawnStartFunc = _Function;
	}
	void SetSpawnCallFunc(TFunction<void()> _Function)
	{
		SpawnCallFunc = _Function;
	}

private:
	FTimerHandle TimerHandle = {};

	int OnceSpawnCount = 0;
	int MaxSpawnCount = 0;
	int CurrentSpawnCount = 0;

	FVector SpawnRange = FVector::ZeroVector;
	UClass* SpawningActor = nullptr;

	TFunction<void()> SpawnStartFunc = nullptr;
	TFunction<void()> SpawnCallFunc = nullptr;

};
