// Coded By AssortRock Unreal Engine Class Project


#include "StageSystem/Stages/ReinforceStage.h"

#include "UpgradeSystem/UpgradeSystem.h"
#include "StageSystem/StageSystem.h"
#include "MainGame/MainGamePlayerState.h"



UReinforceStage::UReinforceStage()
{
	bIsUsingTimer = true;
	TimerToSet = 5.0f;
}

void UReinforceStage::BeginPlay(UStageSystem* NewStageSystem)
{
	Super::BeginPlay(NewStageSystem);

	OnEnterStageInternal.AddDynamic(this, &UReinforceStage::OnReinforceStageEnter);
	// OnEnterStageInternal.AddDynamic(UUpgradeSystem::Get(NewStageSystem->GetWorld()), &UUpgradeSystem::OnReinforceStageEnter);
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
		SetTimer(TimerToSet);
	}

	if (AMainGamePlayerState* MPS = StageSystem->GetWorld()->GetFirstPlayerController()->GetPlayerState<AMainGamePlayerState>())
	{
		// MPS->AddUpgradePoints(1);
	}
}
