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
	void BeginPlay() override;

	void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(BlueprintCallable)
	void SpawnEnemySpawner(FMonsterDataRow MonsterRow, FVector Location);

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
};
