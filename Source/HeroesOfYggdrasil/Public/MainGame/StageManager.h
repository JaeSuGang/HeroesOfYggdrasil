// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "StageManager.generated.h"

class APlayerSelectZone;

UENUM()
enum class EGameStage : uint8
{
	PreStart,
	Reinforce,
	Battle,
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

protected:
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(Server, Reliable)
	void StartGame();

	UFUNCTION(Server, Reliable)
	void OnUpdateStage();

	UFUNCTION(Server, Reliable)
	void OnExitStage();

	UFUNCTION(Server, Reliable)
	void EnterStage(EGameStage newStage, int nRound);

public:
	UFUNCTION(NetMulticast, Reliable)
	void ForceMainWidgetToClients();

public:
	UPROPERTY(Replicated, VisibleInstanceOnly)
	EGameStage CurrentStage;

	UPROPERTY(Replicated, VisibleInstanceOnly)
	int32 Round;

	UPROPERTY(VisibleInstanceOnly, Category = YGG)
	TArray<APlayerSelectZone*> PlayerZones;
};
