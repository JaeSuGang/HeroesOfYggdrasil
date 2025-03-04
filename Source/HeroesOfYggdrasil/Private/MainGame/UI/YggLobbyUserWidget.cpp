// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggLobbyUserWidget.h"
#include "MainGame/UI/YggLobbySelectUserWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"


void UYggLobbyUserWidget::AddPlayerToLobby()
{
	if (!SelectUserWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	UYggLobbySelectUserWidget* NewPlayerWidget = CreateWidget<UYggLobbySelectUserWidget>(GetWorld(), SelectUserWidgetClass);
	if (NewPlayerWidget)
	{
		LobbyCanvasPanel->AddChild(NewPlayerWidget);
		LobbySelectWidget.Add(NewPlayerWidget);
		
		float NewXPosition = LobbySelectWidget.Num() * WidgetSpace;

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(NewPlayerWidget->Slot))
		{
			CanvasSlot->SetPosition(FVector2D(-400.0f + NewXPosition, -150.0f));
		}
	}
}
