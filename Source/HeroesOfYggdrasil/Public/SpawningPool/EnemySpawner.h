// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.generated.h"

UCLASS()
class HEROESOFYGGDRASIL_API AEnemySpawner : public AActor
{
	GENERATED_BODY()
	friend class USpawnManagerComponent;

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
	void SpawnStart();

	UFUNCTION(BlueprintCallable, Server, Reliable)
	void OnceSpawningCall(UClass* _Class, int32 _Count, double _Delay);
	void OnceSpawningCall_Implementation(UClass* _Class, int32 _Count, double _Delay);

private:
	FTimerHandle TimerHandle = {};

	int OnceSpawnCount = 0;
	int MaxSpawnCount = 0;
	int CurrentSpawnCount = 0;

	FVector SpawnRange = FVector::ZeroVector;
	UClass* SpawningActor = nullptr;
	float SpawnDaley = 0.f;

	bool Invalid = false;
};
