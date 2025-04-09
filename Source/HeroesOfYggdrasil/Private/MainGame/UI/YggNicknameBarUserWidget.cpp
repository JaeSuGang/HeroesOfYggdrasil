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


	//if (PlayerName)
	//{
	//	SetPlayerName();
	//}
	//else
	//{
	//	UE_LOG(LogTemp, Error, TEXT("PlayerName is nullptr! Check BindWidget binding."));
	//}
}

void UYggNicknameBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PC = GetOwningPlayer();

	AMainGameHUD* HUD = Cast<AMainGameHUD>(PC->GetHUD());

	HUD->OnSetNickname.RemoveDynamic(this, &UYggNicknameBarUserWidget::SetPlayerName);

	HUD->OnSetNickname.AddDynamic(this, &UYggNicknameBarUserWidget::SetPlayerName);
}

void UYggNicknameBarUserWidget::SetPlayerName()
{
	SetVisibility(ESlateVisibility::Visible);

	//APlayerController* PC = GetOwningPlayer();
	//
	//if (nullptr == PC)
	//{
	//	UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == PC)"), __FUNCTION__, __LINE__);
	//	return;
	//}

	AYggPlayerState* PS = Cast<APawn>(NicknameBarComponent->GetOwner())->GetPlayerState<AYggPlayerState>();

	if (nullptr == PS)
	{
		UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == PS)"), __FUNCTION__, __LINE__);
		return;
	}

	FString Name = PS->GetPlayerName();

	PlayerName->SetText(FText::FromString(Name));
}
