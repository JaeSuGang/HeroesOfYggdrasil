// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggAbilityPlusUserWidget.h"
#include "MainGame/UI/MainGameHUD.h"
#include "Components/Button.h"

void UYggAbilityPlusUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlusButton = Cast<UButton>(GetWidgetFromName(TEXT("PlusButton")));

	APlayerController* PC = GetOwningPlayer();

	AMainGameHUD* MainGameHUD = Cast<AMainGameHUD>(PC->GetHUD());

	if (PlusButton)
	{
		PlusButton->OnClicked.AddDynamic(MainGameHUD, &AMainGameHUD::PlusButtonEvent);
	}
}