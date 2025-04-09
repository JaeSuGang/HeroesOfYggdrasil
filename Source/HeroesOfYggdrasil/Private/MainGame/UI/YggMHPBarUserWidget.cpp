// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggMHPBarUserWidget.h"
#include "Components/ProgressBar.h"

// Player
#include "Player/YggHero.h"
#include "Core/YggCharacter.h"

// Attribute
#include "Attribute/CharacterAttributeComponent.h"

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

    if (IsValid(CAC))
    {
        //CAC->ClientDelegate_OnTakeDamage.AddDynamic(this, &UYggMHPBarUserWidget::UpdateHPBar);
    }
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

void UYggMHPBarUserWidget::SetAttachedCharacter(AEnemyCharacter* Enemy)
{
    if (Enemy != nullptr)
    {
        //EnemyCharacter = Cast<AEnemyCharacter>(Enemy);
        EnemyCharacter = Enemy;
        CAC = EnemyCharacter->GetAttributeComponent();
    }
}