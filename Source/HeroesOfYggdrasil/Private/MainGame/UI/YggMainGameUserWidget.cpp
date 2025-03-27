// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggMainGameUserWidget.h"
#include "MainGame/UI/YggPlayerStatusUserWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void UYggMainGameUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	if (!PlayerStatusUserWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	PlayerStatusWidget = CreateWidget<UYggPlayerStatusUserWidget>(GetWorld(), PlayerStatusUserWidgetClass);

	if (PlayerStatusWidget)
	{
		MainGamePanel->AddChild(PlayerStatusWidget);

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(PlayerStatusWidget->Slot))
		{
			CanvasSlot->SetAlignment(FVector2D(0.0f, 0.0f));
			CanvasSlot->SetAnchors(FAnchors(0.0f, 0.0f));
			CanvasSlot->SetPosition(FVector2D(10.0f, 10.0f));
		}
	}

	if (!OrderStatusUserWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

}
