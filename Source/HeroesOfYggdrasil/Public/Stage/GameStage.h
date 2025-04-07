// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"

#include "Data/YggStructData.h"

#include "GameStage.generated.h"


/*
* 담당 코더 : 김경민
*/
UCLASS()
class HEROESOFYGGDRASIL_API AGameStage : public AActor
{
	GENERATED_BODY()
	
public:	
	AGameStage();

protected:
	void Tick(float fDeltaTime) override;

	void BeginPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	/* 다음 스테이지에 자동으로 진입되는 조건을 블루프린트에서 Override하여 구현하면 됨 */
	UFUNCTION(BlueprintNativeEvent)
	bool ShouldEnterNextStage();

public:
	UFUNCTION(BlueprintCallable)
	void SpawnEnemySpawner(FMonsterDataRow MonsterRow, FVector Location, int nEnemyCount, float fDelay);

	UFUNCTION(Server, Reliable)
	void EnterNextStage();

	UFUNCTION(BlueprintNativeEvent)
	void OnExitStage();

	UFUNCTION(BlueprintNativeEvent)
	void OnEnterStage();

public:
	UPROPERTY(EditAnywhere, Category = "YGG")
	TSubclassOf<AGameStage> NextStage;

	UPROPERTY(Replicated, VisibleInstanceOnly, BlueprintReadWrite)
	int Round;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	float Timer;

	UPROPERTY(VisibleInstanceOnly, BlueprintReadWrite)
	bool bIsTimerEnabled;
};
