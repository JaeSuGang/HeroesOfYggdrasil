// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggNicknameBarUserWidget.h"

#include "Core/YggPlayerState.h"
#include "Components/TextBlock.h"

#include "MainGame/StageManager.h"
#include "MainGame/GameStage.h"
#include "MainGame/UI/MainGameHUD.h"

#include "Component/NicknameBarComponent.h"

void UYggNicknameBarUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetVisibility(ESlateVisibility::Hidden);

}

void UYggNicknameBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UYggNicknameBarUserWidget::SetPlayerName()
{
	SetVisibility(ESlateVisibility::Visible);

	AYggPlayerState* PS = Cast<APawn>(NicknameBarComponent->GetOwner())->GetPlayerState<AYggPlayerState>();

	if (nullptr == PS)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == PS)"), __FUNCTION__, __LINE__);
		return;
	}

	FString Name = PS->GetPlayerName();

	PlayerName->SetText(FText::FromString(Name));
}
