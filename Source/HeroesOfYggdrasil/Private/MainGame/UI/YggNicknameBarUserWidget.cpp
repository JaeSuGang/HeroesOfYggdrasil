// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggNicknameBarUserWidget.h"

#include "Core/YggPlayerState.h"
#include "Components/TextBlock.h"

void UYggNicknameBarUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	if (PlayerName)
	{
		SetPlayerName();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("PlayerName is nullptr! Check BindWidget binding."));
	}
}

void UYggNicknameBarUserWidget::SetPlayerName()
{
	APlayerController* PC = GetOwningPlayer();
	AYggPlayerState* PS = PC->GetPlayerState<AYggPlayerState>();
	FString Name = PS->GetPlayerName();

	PlayerName->SetText(FText::FromString(Name));
}
