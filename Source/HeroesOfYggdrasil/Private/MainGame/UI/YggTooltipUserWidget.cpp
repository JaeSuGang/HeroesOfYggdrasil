// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggTooltipUserWidget.h"

#include "Components/TextBlock.h"


void UYggTooltipUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();


}

void UYggTooltipUserWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UYggTooltipUserWidget::NativeDestruct()
{
	Super::NativeDestruct();


}

void UYggTooltipUserWidget::SetTipText(const FText& NameText, const FText& DescriptionText)
{
	if (Tooltip)
	{
		FString String = FString::Printf(TEXT("%s\n%s"), *NameText.ToString(), *DescriptionText.ToString());

		Tooltip->SetText(FText::FromString(String));
		Tooltip->SetAutoWrapText(true);
	}
}