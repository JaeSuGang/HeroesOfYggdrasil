// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Core/YggGameState.h"
#include "MainGameState.generated.h"

class AStageManager;
class APlayerManager;
class AEnemyManager;
class AUpgradeManager;
class UUpgradeSystem;
class UStageSystem;


class UTest
{

public:
	int a = 5;
};

/**
 * 담당 코더 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API AMainGameState : public AYggGameState
{
	GENERATED_BODY()

public:
	AMainGameState();

protected:
	void BeginPlay() override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(BlueprintCallable)
	AStageManager* GetStageManager() const;

	UFUNCTION(BlueprintCallable)
	APlayerManager* GetPlayerManager() const;

	UFUNCTION(BlueprintCallable)
	AEnemyManager* GetEnemyManager() const;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<APlayerManager> PlayerManagerClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AStageManager> StageManagerClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<AEnemyManager> EnemyManagerClass;

	UPROPERTY(Replicated, VisibleInstanceOnly, BlueprintReadWrite)
	AUpgradeManager* UpgradeManager;

	UPROPERTY(Replicated, VisibleInstanceOnly, BlueprintReadWrite)
	APlayerManager* PlayerManager;

	UPROPERTY(Replicated, VisibleInstanceOnly, BlueprintReadWrite)
	AStageManager* StageManager;

	UPROPERTY(Replicated, VisibleInstanceOnly, BlueprintReadWrite)
	AEnemyManager* EnemyManager;
};
