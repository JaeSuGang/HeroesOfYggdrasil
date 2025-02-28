// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "StageManager.generated.h"

UCLASS()
class HEROESOFYGGDRASIL_API UGameStage : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION()
	virtual void OnStageEnter() {};

	UFUNCTION()
	virtual void OnStageExit() {};

	UFUNCTION()
	virtual void OnStageUpdate(float fDeltaTime) {};
};

/**
 * 담당 코더 : 김경민
 */
UCLASS(Blueprintable)
class HEROESOFYGGDRASIL_API AStageManager : public AInfo
{
	GENERATED_BODY()
	
public:
	AStageManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable)
	static AStageManager* Get(UWorld* WorldContext);

public:
	UFUNCTION(NetMulticast, Reliable)
	void OnEnterReadyFinishedGameState();


public:
	UPROPERTY(VisibleInstanceOnly)
	UGameStage* CurrentStage;

	UPROPERTY(VisibleInstanceOnly)
	int32 Round;
};
