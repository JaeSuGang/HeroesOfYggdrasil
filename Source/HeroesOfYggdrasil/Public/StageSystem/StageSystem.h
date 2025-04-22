// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CustomSystem/CustomSystem.h"
#include "StageSystem.generated.h"

class ALevelSequenceActor;
class UStageBase;
class UBattleStage;
class UReinforceStage;

USTRUCT()
struct FOnGameStartParams
{
	GENERATED_BODY()


};

USTRUCT()
struct FOnVictoryParams
{
	GENERATED_BODY()


};

USTRUCT()
struct FOnDefeatedParams
{
	GENERATED_BODY()


};

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnStageStartedDelegate, UStageBase*, NewStage);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGameStarted, FOnGameStartParams, OnGameStartParams);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnVictory, FOnVictoryParams, OnVictoryParams);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDefeated, FOnDefeatedParams, OnDefeatedParams);

UCLASS()
class HEROESOFYGGDRASIL_API UStageSystem : public UCustomSystem
{
	GENERATED_BODY()

public:	
	UStageSystem();
	
	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static UStageSystem* Get(UObject* WorldContextObject);

protected:
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void BeginPlay() override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	virtual void RegisterObjectsToReplicate() override;

	virtual void UnregisterObjectsToReplicate() override;

public:
	UFUNCTION()
	void VictoryInternal();

	UFUNCTION()
	void DefeatInternal();

	UFUNCTION(NetMulticast, Reliable)
	void Multicast_BroadcastStageStart(UStageBase* NewStage);
	void Multicast_BroadcastStageStart_Implementation(UStageBase* NewStage);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastDefeated(FOnDefeatedParams OnDefeatedParams);
	void MulticastDefeated_Implementation(FOnDefeatedParams OnDefeatedParams);

	UFUNCTION(NetMulticast, Reliable)
	void MulticastVictory(FOnVictoryParams OnVictoryParams);
	void MulticastVictory_Implementation(FOnVictoryParams OnVictoryParams);

	UFUNCTION()
	void StartGame();

	UFUNCTION(NetMulticast, Reliable)
	void BroadcastGameStart(FOnGameStartParams OnGameStartParams);
	void BroadcastGameStart_Implementation(FOnGameStartParams OnGameStartParams);

	UFUNCTION()
	void EnterNextStage();

	UFUNCTION()
	void EnterStage(int NewStageIndex);

	UFUNCTION(Server, Reliable)
	void RequestEnterStage(int NewStageIndex);
	void RequestEnterStage_Implementation(int NewStageIndex);

	UFUNCTION()
	void EnterStageInternal(int NewStageIndex);

	UFUNCTION()
	UBattleStage* GetBattleStage() const;

	UFUNCTION()
	UReinforceStage* GetReinforceStage() const;

protected:
	UFUNCTION()
	void PlayDefeatLevelSequence(FOnDefeatedParams OnDefeatedParams);

public:
	UPROPERTY(BlueprintAssignable)
	FOnStageStartedDelegate OnStageStartedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnGameStarted OnGameStarted;

	UPROPERTY(BlueprintAssignable)
	FOnVictory OnVictory;

	UPROPERTY(BlueprintAssignable)
	FOnDefeated OnDefeated;

public:	
	UPROPERTY(Replicated, Instanced, EditAnywhere)
	TArray<UStageBase*> StageCycle;

	UPROPERTY(VisibleAnywhere)
	ALevelSequenceActor* LevelSequenceActor;

	UPROPERTY(Replicated, VisibleAnywhere)
	int CurrentRound;

	UPROPERTY(Replicated, VisibleAnywhere)
	int CurrentStageIndex;

	UPROPERTY(Replicated, VisibleAnywhere)
	float Timer;
};
