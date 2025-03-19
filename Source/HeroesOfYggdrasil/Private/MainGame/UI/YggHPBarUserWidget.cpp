// Coded By AssortRock Unreal Engine Class Project

// UI
#include "MainGame/UI/YggHPBarUserWidget.h"
#include "Components/ProgressBar.h"

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

    APlayerController* PC = GetOwningPlayer();
    
    UCharacterAttributeComponent* CAC = PC->GetPawn()->GetComponentByClass<UCharacterAttributeComponent>();
    
    if (CAC)
    {
        CAC->ClientDelegate_OnHealthChanged.AddDynamic(this, &UYggHPBarUserWidget::UpdateHPBar);
    }
}

void UYggHPBarUserWidget::UpdateHPBar()
{
    APlayerController* PC = GetOwningPlayer();

    UCharacterAttributeComponent* CAC = PC->GetPawn()->GetComponentByClass<UCharacterAttributeComponent>();

    if (CAC)
    {
        if (HPBar)
    	{
		    HPBar->SetPercent(CAC->GetHp() / CAC->GetMaxHp());
    	}
    }
}