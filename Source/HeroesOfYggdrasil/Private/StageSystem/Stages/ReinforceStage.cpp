// Coded By AssortRock Unreal Engine Class Project


#include "StageSystem/Stages/ReinforceStage.h"

#include "StageSystem/StageSystem.h"
#include "MainGame/MainGamePlayerState.h"


UReinforceStage::UReinforceStage()
{
	bIsUsingTimer = true;
}

void UReinforceStage::BeginPlay(UStageSystem* NewStageSystem)
{
	Super::BeginPlay(NewStageSystem);

	OnEnterStageInternal.AddDynamic(this, &UReinforceStage::OnReinforceStageEnter);
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

void UReinforceStage::OnReinforceStageEnter(FOnEnterStageParams OnEnterStageParams)
{
	if (StageSystem->GetOwner()->HasAuthority())
	{
		SetTimer(20.0f);
	}

	if (AMainGamePlayerState* MPS = StageSystem->GetWorld()->GetFirstPlayerController()->GetPlayerState<AMainGamePlayerState>())
	{
		// MPS->AddUpgradePoints(1);
	}
}
