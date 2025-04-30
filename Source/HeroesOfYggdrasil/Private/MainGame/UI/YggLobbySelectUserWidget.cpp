// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggLobbySelectUserWidget.h"
#include "MainGame/PlayerSelectZone.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Components/Button.h"
#include "Components/EditableTextBox.h"

void UYggLobbySelectUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	LeftButton = Cast<UButton>(GetWidgetFromName(TEXT("LeftButton")));
	RightButton = Cast<UButton>(GetWidgetFromName(TEXT("RightButton")));

	if (LeftButton)
	{
		LeftButton->OnClicked.AddDynamic(this, &UYggLobbySelectUserWidget::LeftButtonEvent);
	}
	
	if (RightButton)
	{
		RightButton->OnClicked.AddDynamic(this, &UYggLobbySelectUserWidget::RightButtonEvent);
	}
}

void UYggLobbySelectUserWidget::LeftButtonEvent()
{
	if (APlayerSelectZone* SelectZone = Cast<APlayerSelectZone>(GetOwningPlayerPawn()))
	{
		SelectZone->SpawnNextSelectable(-1);
	}

	if (ClickSound)
	{
		UGameplayStatics::PlaySound2D(this, ClickSound);
	}
}

void UYggLobbySelectUserWidget::RightButtonEvent()
{
	if (APlayerSelectZone* SelectZone = Cast<APlayerSelectZone>(GetOwningPlayerPawn()))
	{
		SelectZone->SpawnNextSelectable(1);
	}

	if (ClickSound)
	{
		UGameplayStatics::PlaySound2D(this, ClickSound);
	}
}

FString UYggLobbySelectUserWidget::GetTextBlockValue()
{
	if (Nickname)
	{
		return Nickname->GetText().ToString();
	}

	return FString(" ");
}
