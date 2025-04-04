// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggCastingBarUserWidget.h"

#include "Attribute/HeroAttributeComponent.h"
#include "Components/ProgressBar.h"


void UYggCastingBarUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	SetVisibility(ESlateVisibility::Collapsed);
}

void UYggCastingBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	
}

void UYggCastingBarUserWidget::StartCasting(float Duration)
{
	CastingTime = Duration;
	RemainingTime = Duration;

	if (CastingBar)
	{
		CastingBar->SetPercent(1.0f);
		SetVisibility(ESlateVisibility::Visible);
	}

	GetWorld()->GetTimerManager().SetTimer(CastingTimerHandle, this, &UYggCastingBarUserWidget::UpdateCastingBar, 0.05f, true);
}

void UYggCastingBarUserWidget::UpdateCastingBar()
{
	RemainingTime -= 0.05f;

	if (RemainingTime <= 0.0f)
	{
		EndCasting();
		return;
	}

	float Progress = RemainingTime / CastingTime;
	if (CastingBar)
	{
		CastingBar->SetPercent(Progress);
	}
}

void UYggCastingBarUserWidget::EndCasting()
{
	GetWorld()->GetTimerManager().ClearTimer(CastingTimerHandle);

	SetVisibility(ESlateVisibility::Collapsed);
}