// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggAbilityUserWidget.h"
#include "MainGame/UI/MainGameHUD.h"

#include "Components/Button.h"

void UYggAbilityUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SelectButton = Cast<UButton>(GetWidgetFromName(TEXT("SelectButton")));

	APlayerController* PC = GetOwningPlayer();

	AMainGameHUD* MainGameHUD = Cast<AMainGameHUD>(PC->GetHUD());

	if (SelectButton)
	{
		SelectButton->OnClicked.AddDynamic(MainGameHUD, &AMainGameHUD::AbilitySelectEvent);
	}
}
