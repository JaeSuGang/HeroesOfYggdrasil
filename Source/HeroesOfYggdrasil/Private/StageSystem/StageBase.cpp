// Coded By AssortRock Unreal Engine Class Project


#include "StageSystem/StageBase.h"

#include "Net/UnrealNetwork.h"

#include "StageSystem/StageSystem.h"

UStageBase::UStageBase()
{
	
}

bool UStageBase::IsSupportedForNetworking() const
{
	return true;
}

void UStageBase::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

}

void UStageBase::BeginPlay(UStageSystem* NewStageSystem)
{
	StageSystem = NewStageSystem;
}

void UStageBase::TickLogic(float fDeltaTime)
{

}

void UStageBase::Local_OnEnterStage(int NewRound)
{
	FOnEnterStageDelegateParams OnEnterStageDelegateParams{};
	OnEnterStageDelegateParams.NewRound = NewRound;

	OnEnterStageDelegate.Broadcast(OnEnterStageDelegateParams);
}

void UStageBase::Local_OnExitStage(int CurrentRound)
{
	FOnExitStageDelegateParams OnExitStageDelegateParams{};
	OnExitStageDelegateParams.CurrentRound = CurrentRound;

	OnExitStageDelegate.Broadcast(OnExitStageDelegateParams);
}

void UStageBase::EnterNextStage()
{
	StageSystem->EnterNextStage();
}

void UStageBase::SetTimer(float fTime)
{
	StageSystem->Timer = fTime;
}

float UStageBase::GetTimer() const
{
	return StageSystem->Timer;
}

