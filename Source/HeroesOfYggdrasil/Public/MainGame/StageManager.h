// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "StageManager.generated.h"

UCLASS(Abstract)
class HEROESOFYGGDRASIL_API UGameStage : public UObject
{
	GENERATED_BODY()

public:
	/* 서버만이 호출하도록 요망 */
	UFUNCTION(NetMulticast, Reliable)
	virtual void OnStateEnter_NetMulticast() = 0;

	UFUNCTION(NetMulticast, Reliable)
	virtual void OnStateUpdate_NetMulticast() = 0;

	UFUNCTION(NetMulticast, Reliable)
	virtual void OnStateExit_NetMulticast() = 0;

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

};
