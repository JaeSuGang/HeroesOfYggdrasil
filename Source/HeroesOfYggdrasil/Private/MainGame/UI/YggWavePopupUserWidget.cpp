// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggWavePopupUserWidget.h"

#include "Components/TextBlock.h"
#include "StageSystem/StageSystem.h"
#include "StageSystem/StageBase.h"

void UYggWavePopupUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	UStageSystem* StageSystem = UStageSystem::Get(GetWorld());
}

void UYggWavePopupUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UYggWavePopupUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

}
