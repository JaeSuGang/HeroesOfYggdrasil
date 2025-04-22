// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "StageSystem/StageBase.h"
#include "ReinforceStage.generated.h"

/**
 * 담당 프로그래머 : 김경민
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
	void OnReinforceStageEnter(FOnEnterStageDelegateParams OnEnterStageParams);

	virtual void Local_OnExitStage(int CurrentRound) override;

	virtual void Local_OnEnterStage(int NewRound) override;

public:
	UPROPERTY(EditAnywhere)
	float TimerToSet;
};
