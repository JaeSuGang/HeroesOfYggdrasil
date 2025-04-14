// Coded By AssortRock Unreal Engine Class Project

#include "StageSystem/StageSystem.h"

#include "GameFramework/GameState.h"
#include "Net/UnrealNetwork.h"

#include "StageSystem/StageBase.h"
#include "StageSystem/Stages/BattleStage.h"
#include "StageSystem/Stages/ReinforceStage.h"
#include "MainGame/PlayerSelectZone.h"
#include "MainGame/UI/MainGameHUD.h"

UStageSystem::UStageSystem()
{
	bReplicateUsingRegisteredSubObjectList = true;
	SetIsReplicatedByDefault(true);
}

UStageSystem* UStageSystem::Get(UObject* WorldContextObject)
{
	if (AGameState* GameState = WorldContextObject->GetWorld()->GetGameState<AGameState>())
	{
		UStageSystem* StageSystem = GameState->GetComponentByClass<UStageSystem>();
		return StageSystem;
	}

	return nullptr;
}

void UStageSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	if (CurrentRound > 0)
	{
		StageCycle[CurrentStageIndex]->TickLogic(DeltaTime);
	}

	Timer -= DeltaTime;
	if (Timer < 0.0f)
		Timer = 0.0f;
}

void UStageSystem::BeginPlay()
{
	Super::BeginPlay();

	for (UStageBase* Stage : StageCycle)
	{
		Stage->BeginPlay(this);
	}
}

void UStageSystem::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UStageSystem, StageCycle);
	DOREPLIFETIME(UStageSystem, CurrentStageIndex);
}

void UStageSystem::RegisterObjectsToReplicate()
{
	for (UStageBase* Stage : StageCycle)
	{
		AddReplicatedSubObject(Stage);
	}
}

void UStageSystem::UnregisterObjectsToReplicate()
{
	for (UStageBase* Stage : StageCycle)
	{
		RemoveReplicatedSubObject(Stage);
	}
}

void UStageSystem::ForceMainWidgetsToClient_Implementation()
{
	if (APlayerController* PC = GetWorld()->GetFirstPlayerController())
	{
		if (AMainGameHUD* MGH = Cast<AMainGameHUD>(PC->GetHUD()))
		{
			MGH->CloseCurrentWidget();
			MGH->ShowMainGameWidget();
		}
	}
}

void UStageSystem::StartGame()
{
	auto ControllerIter = GetWorld()->GetPlayerControllerIterator();
	while (ControllerIter)
	{
		APlayerController* PC = ControllerIter->Get();
		if (APlayerSelectZone* PSZ = Cast<APlayerSelectZone>(PC->GetPawn()))
		{
			PSZ->SelectCharacter();
		}
		++ControllerIter;
	}

	EnterStage(0);
	ForceMainWidgetsToClient();
}

void UStageSystem::EnterNextStage()
{
	EnterStage(CurrentStageIndex + 1);
}

void UStageSystem::EnterStage(int NewStageIndex)
{
	if (GetOwner()->HasAuthority())
	{
		EnterStageInternal(NewStageIndex);
	}
	else
	{
		RequestEnterStage(NewStageIndex);
	}
}

void UStageSystem::RequestEnterStage_Implementation(int NewStageIndex)
{
	EnterStageInternal(NewStageIndex);
}

void UStageSystem::EnterStageInternal(int NewStageIndex)
{
	/* Delegate 인자 설정 */
	FOnExitStageParams OnExitStageParams{};
	OnExitStageParams.PrevRound = CurrentRound;
	OnExitStageParams.NewRound = CurrentRound + 1;

	FOnEnterStageParams OnEnterStageParams{};
	OnEnterStageParams.PrevRound = CurrentRound;
	OnEnterStageParams.NewRound = CurrentRound + 1;

	/* 스테이지 진입과 Delegate 호출 */
	UStageBase* OldStage = StageCycle[CurrentStageIndex];
	OldStage->OnExitStageInternal.Broadcast(OnExitStageParams);

	CurrentStageIndex = ++CurrentStageIndex % StageCycle.Num();
	if (CurrentStageIndex == 0)
	{
		CurrentRound++;
	}

	UStageBase* NewStage = StageCycle[CurrentStageIndex];
	NewStage->Round = CurrentRound;
	NewStage->OnEnterStageInternal.Broadcast(OnEnterStageParams);
}

UBattleStage* UStageSystem::GetBattleStage() const
{
	for (UStageBase* Stage : StageCycle)
	{
		if (UBattleStage* CastedStage = Cast<UBattleStage>(Stage))
		{
			return CastedStage;
		}
	}
	return nullptr;
}

UReinforceStage* UStageSystem::GetReinforceStage() const
{
	for (UStageBase* Stage : StageCycle)
	{
		if (UReinforceStage* CastedStage = Cast<UReinforceStage>(Stage))
		{
			return CastedStage;
		}
	}
	return nullptr;
}


