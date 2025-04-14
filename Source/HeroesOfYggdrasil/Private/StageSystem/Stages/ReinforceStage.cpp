// Coded By AssortRock Unreal Engine Class Project


#include "StageSystem/Stages/ReinforceStage.h"

#include "StageSystem/StageSystem.h"

UReinforceStage::UReinforceStage()
{
	bIsUsingTimer = true;
}

void UReinforceStage::BeginPlay(UStageSystem* NewStageSystem)
{
	Super::BeginPlay(NewStageSystem);

	if (StageSystem->GetOwner()->HasAuthority())
	{
		OnEnterStageInternal.AddDynamic(this, &UReinforceStage::SetReinforceStageSetting);
	}
}

void UReinforceStage::TickLogic(float fDeltaTime)
{
	Super::TickLogic(fDeltaTime);

	if (StageSystem->GetOwner()->HasAuthority())
	{
		if (GetTimer() <= 0.0f)
		{
			EnterNextStage();
		}
	}
}

void UReinforceStage::SetReinforceStageSetting(FOnEnterStageParams OnEnterStageParams)
{
	SetTimer(20.0f);
}
