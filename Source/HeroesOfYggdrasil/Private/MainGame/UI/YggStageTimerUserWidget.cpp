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

	StageTimer->SetText(FText::AsNumber(StageSystem->Timer));
}
