// Coded By AssortRock Unreal Engine Class Project


#include "StageSystem/Stages/ReinforceStage.h"

#include "UpgradeSystem/UpgradeSystem.h"
#include "StageSystem/StageSystem.h"
#include "MainGame/MainGamePlayerState.h"
#include "MainGame/MainGameState.h"



UReinforceStage::UReinforceStage()
{
	bIsUsingTimer = true;
	TimerToSet = 5.0f;
}

void UReinforceStage::BeginPlay(UStageSystem* NewStageSystem)
{
	Super::BeginPlay(NewStageSystem);

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

void UReinforceStage::Authority_AddUpgradePoints()
{
	if (StageSystem->GetOwner()->HasAuthority())
	{
		SetTimer(TimerToSet);

		if (AMainGameState* MGS = StageSystem->GetWorld()->GetGameState<AMainGameState>())
		{
			if (UUpgradeSystem* US = UUpgradeSystem::Get(StageSystem->GetWorld()))
			{
				for (APlayerState* PS : MGS->PlayerArray)
				{
					US->AddUpgradePointInternal(PS);
				}
			}
		}
	}
}

void UReinforceStage::Local_OnExitStage(int CurrentRound)
{
	Super::Local_OnExitStage(CurrentRound);
}

void UReinforceStage::Local_OnEnterStage(int NewRound)
{
	Super::Local_OnEnterStage(NewRound);

	if (StageSystem->GetOwner()->GetOwner())
	{
		Authority_AddUpgradePoints();
	}
}
