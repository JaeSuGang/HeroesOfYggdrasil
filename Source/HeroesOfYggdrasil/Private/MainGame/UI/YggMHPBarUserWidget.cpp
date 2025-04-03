// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggMHPBarUserWidget.h"
#include "Components/ProgressBar.h"

// Player
#include "Player/YggHero.h"
#include "Core/YggCharacter.h"

// Attribute
#include "Attribute/CharacterAttributeComponent.h"

// Data
#include "Engine/DataTable.h"
#include "Data/YggStructData.h"

#include "Enemy/EnemyCharacter.h"
#include "Components/WidgetComponent.h"

#include "Components/SceneComponent.h"

void UYggMHPBarUserWidget::NativeOnInitialized()
{
    Super::NativeOnInitialized();
    
    SetVisibility(ESlateVisibility::Hidden);
}

void UYggMHPBarUserWidget::NativeConstruct()
{
    Super::NativeConstruct();

}

void UYggMHPBarUserWidget::UpdateHPBar(float HP)
{
    if (IsValid(CAC))
    {
        if (IsValid(HPBar))
        {
            HPBar->SetPercent(CAC->HP / CAC->MaxHP);
        }
    }

    if (GetVisibility() == ESlateVisibility::Hidden)
    {
        SetVisibility(ESlateVisibility::Visible);
    }
}

void UYggMHPBarUserWidget::SetAttachedCharacter(AActor* Character)
{
    EnemyCharacter = Cast<AEnemyCharacter>(Character);
    CAC = EnemyCharacter->GetEnemyAttributeComponent();
}