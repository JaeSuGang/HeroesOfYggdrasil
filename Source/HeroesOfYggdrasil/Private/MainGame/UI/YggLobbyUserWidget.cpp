// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggLobbyUserWidget.h"
#include "MainGame/UI/YggLobbySelectUserWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"
#include "Components/Widget.h"
#include "MainGame/MainGameState.h"
#include "MainGame/MainGamePlayerState.h"
#include "MainGame/PlayerSelectZone.h"

void UYggLobbyUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
}

void UYggLobbyUserWidget::AddPlayerToLobby()
{
	if (!SelectUserWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);
	//GetOwningPlayer()->GetPlayerState<AMainGamePlayerState>()->GetPlayerId();
	
	UYggLobbySelectUserWidget* NewPlayerWidget = CreateWidget<UYggLobbySelectUserWidget>(GetWorld(), SelectUserWidgetClass);
	
	if (NewPlayerWidget)
	{
		LobbyCanvasPanel->AddChild(NewPlayerWidget);
		//LobbySelectWidget = NewPlayerWidget;

		//float NewXPosition = i * WidgetSpace;

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(NewPlayerWidget->Slot))
		{
			CanvasSlot->SetPosition(FVector2D(0.0f, 225.0f));
			CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
			CanvasSlot->SetAnchors(FAnchors(0.5f, 0.5f));
		}
	}
	//
	//	if (PlayerCount == i)
	//	{
	//		NewPlayerWidget->LeftButton->SetIsEnabled(true);
	//		NewPlayerWidget->RightButton->SetIsEnabled(true);
	//	}
	//	else
	//	{
	//		NewPlayerWidget->LeftButton->SetIsEnabled(false);
	//		NewPlayerWidget->RightButton->SetIsEnabled(false);
	//	}
	//}

}



