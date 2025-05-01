// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggStageTimerUserWidget.h"

#include "Core/YggPlayerState.h"
#include "Components/TextBlock.h"

#include "StageSystem/StageSystem.h"
#include "StageSystem/StageBase.h"


void UYggStageTimerUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetVisibility(ESlateVisibility::Visible);
	
	if (StageTimer)
	{
		GetStageTimer();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("StageTimer is nullptr! Check BindWidget binding."));
	}
}

void UYggStageTimerUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (UStageSystem* StageSystem = UStageSystem::Get(GetWorld()))
	{
		StageSystem->OnStageStartedDelegate.AddDynamic(this, &UYggStageTimerUserWidget::UpdateTimer);
	}
}

void UYggStageTimerUserWidget::UpdateTimer(UStageBase* NewStage, int NewRound)
{
	UStageSystem* StageSystem = UStageSystem::Get(GetWorld());
	
	if (nullptr == StageSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == StageManager)"), __FUNCTION__, __LINE__);
		return;
	}
	
	if (StageSystem->StageCycle[StageSystem->CurrentStageIndex]->bIsUsingTimer)
	{
		SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		SetVisibility(ESlateVisibility::Hidden);
	}
	
	GetStageTimer();
}

void UYggStageTimerUserWidget::GetStageTimer()
{
	UStageSystem* StageSystem = UStageSystem::Get(GetWorld());

	if (nullptr == StageSystem)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == StageManager)"), __FUNCTION__, __LINE__);
		return;
	}

	FString String = FString::Printf(TEXT("%.1f s"), StageSystem->Timer);

	StageTimer->SetText(FText::FromString(String));
}
