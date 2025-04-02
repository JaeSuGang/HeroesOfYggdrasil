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

    HPBar->SetPercent(100 / 100);

    SetVisibility(ESlateVisibility::Visible);
}

void UYggMHPBarUserWidget::NativeConstruct()
{
    Super::NativeConstruct();
    UWidgetComponent* OwningWidgetComp = Cast<UWidgetComponent>(GetOuter());

    //if (IsValid(OwningWidgetComp))
    //{
    //    // WidgetComponent가 붙어있는 Actor 얻기
    //    AActor* OwnerActor = OwningWidgetComp->GetOwner();
    //    if (IsValid(OwnerActor))
    //    {
    //        UE_LOG(LogTemp, Log, TEXT("Attach된 액터: %s"), OwnerActor->GetName());
    //    }

    //    // 혹은 Component Parent (부모 SceneComponent)
    //    USceneComponent* WidgetAttachParent = OwningWidgetComp->GetAttachParent();
    //    if (IsValid(WidgetAttachParent))
    //    {
    //        UE_LOG(LogTemp, Log, TEXT("Attach Parent Component: %s"), *WidgetAttachParent->GetName());
    //    }
    //}

    FTimerHandle TestHandle{};
    GetWorld()->GetTimerManager().SetTimer(TestHandle, this, &UYggMHPBarUserWidget::Test, 1.0f, false);
   

    //UWidgetComponent* WidgetComp = GetTypedOuter<UWidgetComponent>();
    //if (!WidgetComp)
    //{
    //    UE_LOG(LogTemp, Error, TEXT("WidgetComp not found in GetTypedOuter!"));
    //}
    //

    
    //if (WidgetComponent)
    //{
    //    WidgetInstance = Cast<UYggMHPBarUserWidget>(WidgetComponent->GetUserWidgetObject());
    //    if (WidgetInstance)
    //    {
    //        WidgetInstance->SetOwningActor(this);  // 몬스터(자신)를 위젯에 전달
    //    }
    //}


   /* EnemyCharacter = Cast<AEnemyCharacter>(OwningActor);
    if (!EnemyCharacter)
    {
        UE_LOG(LogTemp, Error, TEXT("EnemyCharacter is nullptr!"));
    }*/
    //
    //UCharacterAttributeComponent* CAC = EnemyCharacter->GetAttributeComponent();
    //
    //if (IsValid(CAC))
    //{
    //    CAC->ClientDelegate_OnTakeDamage.AddDynamic(this, &UYggMHPBarUserWidget::UpdateHPBar);
    //}
}
UWidgetComponent* UYggMHPBarUserWidget::GetOwningWidgetComponent()
{
    UObject* Outer = GetOuter();
    while (Outer)
    {
        if (UWidgetComponent* WidgetComp = Cast<UWidgetComponent>(Outer))
        {
            return WidgetComp;
        }
        Outer = Outer->GetOuter(); // 부모 객체로 이동
    }
    return nullptr;
}

// 위젯 컴포넌트를 소유한 액터 가져오기
AActor* UYggMHPBarUserWidget::GetOwningActorFromWidget(UUserWidget* Widget)
{
    if (UWidgetComponent* WidgetComp = GetOwningWidgetComponent())
    {
        return WidgetComp->GetOwner();
    }
    return nullptr;
}

void UYggMHPBarUserWidget::Test()
{
    GetOwningWidgetComponent();
}




void UYggMHPBarUserWidget::UpdateHPBar(float HP)
{
    UCharacterAttributeComponent* CAC = EnemyCharacter->GetAttributeComponent();

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
}