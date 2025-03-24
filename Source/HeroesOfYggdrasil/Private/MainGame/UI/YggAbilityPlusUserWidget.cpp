// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggAbilityPlusUserWidget.h"
#include "Components/Button.h"

void UYggAbilityPlusUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	PlusButton = Cast<UButton>(GetWidgetFromName(TEXT("PlusButton")));

	if (PlusButton)
	{
		PlusButton->OnClicked.AddDynamic(this, &UYggAbilityPlusUserWidget::PlusButtonEvent);
	}
}

void UYggAbilityPlusUserWidget::PlusButtonEvent()
{

}
