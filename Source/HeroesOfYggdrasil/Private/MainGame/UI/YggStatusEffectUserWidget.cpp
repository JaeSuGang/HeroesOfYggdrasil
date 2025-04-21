// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggStatusEffectUserWidget.h"

#include "MainGame/UI/YggDebuffUserWidget.h"
#include "Components/HorizontalBox.h"

#include "Player/YggHero.h"
#include "Attribute/HeroAttributeComponent.h"

void UYggStatusEffectUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UYggStatusEffectUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AYggHero* Hero = PC->GetPawn<AYggHero>();
	UHeroAttributeComponent* HAC = Hero->GetHeroAttributeComponent();

	HAC->OnTagsChanged.AddDynamic(this, &UYggStatusEffectUserWidget::UpdateDebuff);

}

void UYggStatusEffectUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UYggStatusEffectUserWidget::UpdateDebuff(FOnTagsChangedParams OnTagsChangedParams)
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AYggHero* Hero = PC->GetPawn<AYggHero>();
	UHeroAttributeComponent* HAC = Hero->GetHeroAttributeComponent();

	if (HAC->HasTag("Debuff.Poison"))
	{
		//if (UYggDebuffUserWidget* Existing = FindDebuffWidget(EStatusEffectType::Poison))
		//{
		//	DebuffContainer->RemoveChild(Existing);
		//	DebuffWidgets.Remove(Existing);
		//}
		if (FindDebuffWidget(EStatusEffectType::Poison))
			return;

		UYggDebuffUserWidget* NewDebuff = CreateWidget<UYggDebuffUserWidget>(this, DebuffUserWidgetClass);
		NewDebuff->InitDebuff(EStatusEffectType::Poison);

		DebuffContainer->AddChild(NewDebuff);
		DebuffWidgets.Add(NewDebuff);
	}
	else if (UYggDebuffUserWidget* Existing = FindDebuffWidget(EStatusEffectType::Poison))
	{
		DebuffContainer->RemoveChild(Existing);
		DebuffWidgets.Remove(Existing);
	}
	

	
}

UYggDebuffUserWidget* UYggStatusEffectUserWidget::FindDebuffWidget(EStatusEffectType StatusEffectType)
{
	for (UYggDebuffUserWidget* Widget : DebuffWidgets)
	{
		if (Widget && Widget->GetDebuffType() == StatusEffectType)
		{
			return Widget;
		}
	}

	return nullptr;
}
