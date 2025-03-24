// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggNicknameBarUserWidget.h"

#include "Core/YggPlayerState.h"
#include "Components/TextBlock.h"

#include "MainGame/StageManager.h"
#include "MainGame/GameStage.h"

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

	if (nullptr == PC)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == PC)"), __FUNCTION__, __LINE__);
		return;
	}

	AYggPlayerState* PS = PC->GetPlayerState<AYggPlayerState>();

	if (nullptr == PS)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == PS)"), __FUNCTION__, __LINE__);
		return;
	}

	FString Name = PS->GetPlayerName();

	PlayerName->SetText(FText::FromString(Name));
}
