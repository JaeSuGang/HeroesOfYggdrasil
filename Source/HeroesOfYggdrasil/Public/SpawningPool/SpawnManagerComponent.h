// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EnemySpawner.h"
#include "SpawnManagerComponent.generated.h"

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



UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class HEROESOFYGGDRASIL_API USpawnManagerComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	USpawnManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable)
	void StageEnemySpawn(int32 Stage);

public:
	UPROPERTY(VisibleAnywhere, Category = "Data")
	UDataTable* SpawnDatas = nullptr;
};
