// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggFuelBarUserWidget.h"

#include "Attribute/CharacterAttributeComponent.h"

#include "Player/YggHero.h"
#include "Player/YggHeroAurora.h"

#include "Components/ProgressBar.h"


void UYggFuelBarUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

    SetRenderOpacity(0.0f);
}

void UYggFuelBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UYggFuelBarUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
    Super::NativeTick(MyGeometry, InDeltaTime);

    UpdateFuelBar();
}

void UYggFuelBarUserWidget::UpdateFuelBar()
{
    APlayerController* PC = GetOwningPlayer();

    float Percent;

    if (AYggHeroAurora* Hero = PC->GetPawn<AYggHeroAurora>())
    {
        Percent = Hero->CurrentFuel / Hero->MaxJetpackFuel;
                
        FuelBar->SetPercent(Percent);
    }

    if (1.0f <= Percent)
    {
        SetRenderOpacity(0.0f);
    }
    else
    {
        SetRenderOpacity(1.0f);
    }
}