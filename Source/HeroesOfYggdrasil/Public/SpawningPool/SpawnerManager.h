// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "EnemySpawner.h"
#include "SpawnerManager.generated.h"

USTRUCT(BlueprintType)
struct FSpawnPortalData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FSpawnPortalData()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	UClass* SpawnEnemy;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 OnceSpawnCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	int32 MaxSpawnCount = 0;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	float SpawnDaley = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FVector SpawnLocation = FVector::ZeroVector;
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	FVector SpawnRange = FVector::ZeroVector;

};

USTRUCT(BlueprintType)
struct FStageEnemyData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

public:
	FStageEnemyData()
	{
	}

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Data)
	TArray<FSpawnPortalData> EnemyDatas = {};

};


UCLASS()
class HEROESOFYGGDRASIL_API ASpawnerManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnerManager();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void StageEnemySpawn(int32 Stage);

public:
	// TObjectPtr<FStageEnemyData> SpawnDatas = {};
	UPROPERTY(VisibleAnywhere, Category = "Data")
	UDataTable* SpawnDatas = nullptr;

};
