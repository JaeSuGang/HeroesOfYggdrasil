// Coded By AssortRock Unreal Engine Class Project

// UI
#include "MainGame/UI/YggHPBarUserWidget.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

// Player
#include "Player/YggHero.h"
#include "Core/YggCharacter.h"

// Attribute
#include "Attribute/CharacterAttributeComponent.h"

// Data
#include "Engine/DataTable.h"
#include "Data/YggStructData.h"

void UYggHPBarUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UYggHPBarUserWidget::NativeConstruct()
{
    Super::NativeConstruct();
    
    APlayerController* PC = GetOwningPlayer();

    UCharacterAttributeComponent* CAC = PC->GetPawn()->GetComponentByClass<UCharacterAttributeComponent>();

    if (CAC)
    {
        CAC->ClientDelegate_OnTakeDamage.AddDynamic(this, &UYggHPBarUserWidget::UpdateHPBar);
    }

    UpdateHPBar(0);
}

void UYggHPBarUserWidget::UpdateHPBar(float HP)
{
    APlayerController* PC = GetOwningPlayer();

    UCharacterAttributeComponent* CAC = PC->GetPawn()->GetComponentByClass<UCharacterAttributeComponent>();

    if (CAC)
    {
        if (IsValid(HPBar) && IsValid(HPText))
    	{
            FText HealthText = FText::Format(FText::FromString("{0} / {1}"), FText::AsNumber(CAC->HP), FText::AsNumber(CAC->MaxHP));
		    
            HPBar->SetPercent(CAC->HP / CAC->MaxHP);
            HPText->SetText(HealthText);
    	}
    }
}