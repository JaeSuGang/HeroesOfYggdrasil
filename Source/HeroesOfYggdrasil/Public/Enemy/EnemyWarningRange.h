// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Data/YggStructData.h"
#include "EnemyWarningRange.generated.h"

UCLASS()
class HEROESOFYGGDRASIL_API AEnemyWarningRange : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AEnemyWarningRange();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void UpdateRange(float DeltaTime);

	float GetDuration()
	{
		return Duration;
	}

	float GetTimeElapsed()
	{
		return TimeElapsed;
	}

public:

	UPROPERTY(VisibleAnywhere)
	class UStaticMeshComponent* PlaneMesh;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* WarningMaterial;

	UPROPERTY()
	class UMaterialInstanceDynamic* DynamicMaterial;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAOE")
	UDataTable* AOEDataTable;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAOE")
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "EnemyAOE")
	float TimeElapsed;
};
