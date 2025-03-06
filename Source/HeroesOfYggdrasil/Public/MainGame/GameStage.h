// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
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

public:
	UFUNCTION(BlueprintNativeEvent)
	void OnExitStage();

	UFUNCTION(BlueprintNativeEvent)
	void OnEnterStage();
};
