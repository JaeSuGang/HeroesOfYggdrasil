// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "StageManager.generated.h"



class AGameStage;
class UStageManagerDataAsset;

/**
 * 담당 코더 : 김경민
 */
UCLASS(Blueprintable)
class HEROESOFYGGDRASIL_API AStageManager : public AInfo
{
	GENERATED_BODY()
	
public:
	AStageManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

	UFUNCTION(BlueprintCallable, meta = (WorldContext = "WorldContextObject"))
	static AStageManager* Get(UObject* WorldContextObject);

protected:
	void BeginPlay() override;
	void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

public:
	UFUNCTION(Server, Reliable, BlueprintCallable)
	void EnterStage(TSubclassOf<AGameStage> stage);

	UFUNCTION(Server, Reliable, BlueprintCallable)
	void StartGame();



public:
	UFUNCTION(NetMulticast, Reliable, BlueprintCallable)
	void ForceMainWidgetToClients();

public:
	/* Refactored */

	

	/* Deprecated */
	UPROPERTY(EditAnywhere)
	TSubclassOf<AGameStage> FirstStageToStart;

	UPROPERTY(Replicated, VisibleInstanceOnly, BlueprintReadWrite)
	AGameStage* CurrentStage;

	UPROPERTY(Replicated, VisibleInstanceOnly, BlueprintReadWrite)
	int32 Round;


};
