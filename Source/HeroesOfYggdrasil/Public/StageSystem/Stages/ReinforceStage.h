// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "StageSystem/StageBase.h"
#include "ReinforceStage.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UReinforceStage : public UStageBase
{
	GENERATED_BODY()
	
public:
	UReinforceStage();

public:
	virtual void BeginPlay(UStageSystem* NewStageSystem) override;

	virtual void TickLogic(float fDeltaTime) override;

public:
	UFUNCTION()
	void OnReinforceStageEnter(FOnEnterStageParams OnEnterStageParams);
};
