// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggStageTimerUserWidget.h"

#include "Core/YggPlayerState.h"
#include "Components/TextBlock.h"

#include "MainGame/StageManager.h"
#include "MainGame/GameStage.h"


void UYggStageTimerUserWidget::NativeOnInitialized()
{
	SetVisibility(ESlateVisibility::Visible);
	//SetVisibility(ESlateVisibility::Hidden);

	if (StageTimer)
	{
		GetStageTimer();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("StageTimer is nullptr! Check BindWidget binding."));
	}
}

void UYggStageTimerUserWidget::UpdateTimer()
{
	AStageManager* StageManager = AStageManager::Get(GetWorld());

	if (nullptr == StageManager)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == StageManager)"), __FUNCTION__, __LINE__);
		return;
	}

	AGameStage* Stage = StageManager->CurrentStage;
	
	if (nullptr == Stage)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Stage)"), __FUNCTION__, __LINE__);
		return;
	}

	if (Stage->bIsTimerEnabled)
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
	AStageManager* StageManager = AStageManager::Get(GetWorld());

	if (nullptr == StageManager)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == StageManager)"), __FUNCTION__, __LINE__);
		return;
	}

	AGameStage* Stage = StageManager->CurrentStage;

	if (nullptr == Stage)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == Stage)"), __FUNCTION__, __LINE__);
		return;
	}

	AGameStage* Stage = StageManager->CurrentStage;
	if (Stage)
	{
		StageTimer->SetText(FText::AsNumber(Stage->Timer));
	}
}
