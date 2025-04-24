// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggWavePopupUserWidget.h"

#include "Components/TextBlock.h"
#include "StageSystem/StageSystem.h"
#include "StageSystem/StageBase.h"
#include "StageSystem/Stages/BattleStage.h"
#include "StageSystem/Stages/ReinforceStage.h"


void UYggWavePopupUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	SetVisibility(ESlateVisibility::Hidden);

	UStageSystem* StageSystem = UStageSystem::Get(GetWorld());

	StageSystem->OnStageStartedDelegate.AddDynamic(this, &UYggWavePopupUserWidget::UpdateWidget);

	if (WaveAnim)
	{
		EndDelegate.BindDynamic(this, &UYggWavePopupUserWidget::EndAnim);
		BindToAnimationFinished(WaveAnim, EndDelegate);
	}
}

void UYggWavePopupUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UYggWavePopupUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UYggWavePopupUserWidget::UpdateWidget(UStageBase* NewStage)
{
	SetVisibility(ESlateVisibility::Visible);

	if (IsValid(Wave))
	{
		if (UReinforceStage* CastedStage = Cast<UReinforceStage>(NewStage))
		{
			if (0 != (CastedStage->StageSystem->CurrentRound - 1))
			{
				FString String = FString::Printf(TEXT("WAVE %d CLEAR"), (CastedStage->StageSystem->CurrentRound - 1));

				Wave->SetText(FText::FromString(String));
			}
		}

		if (UBattleStage* CastedStage = Cast<UBattleStage>(NewStage))
		{
			FString String = FString::Printf(TEXT("WAVE %d"), CastedStage->StageSystem->CurrentRound);

			Wave->SetText(FText::FromString(String));
		}
	}

	PlayAnimation(WaveAnim);
}

void UYggWavePopupUserWidget::EndAnim()
{
	SetVisibility(ESlateVisibility::Hidden);
}
