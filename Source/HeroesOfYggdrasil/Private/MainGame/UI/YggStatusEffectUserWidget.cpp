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
	if (!PC)
		return;

	AYggHero* Hero = PC->GetPawn<AYggHero>();
	if (!Hero)
		return;

	UCharacterAttributeComponent* HAC = Hero->GetAttributeComponent();
	if (!HAC)
		return;

	if (HAC->HasTag("Character.DeBuff.Poison"))
	{
		if (!FindDebuffWidget(EStatusEffectType::Poison))
		{
			AddDebuff(EStatusEffectType::Poison);
		}
	}
	else
	{
		if (UYggDebuffUserWidget* Existing = FindDebuffWidget(EStatusEffectType::Poison))
		{
			RemoveDebuff(Existing);
		}
	}
	
	if (HAC->HasTag("Character.DeBuff.Burn"))
	{
		if (!FindDebuffWidget(EStatusEffectType::Burn))
		{
			AddDebuff(EStatusEffectType::Burn);
		}
	}
	else
	{
		if (UYggDebuffUserWidget* Existing = FindDebuffWidget(EStatusEffectType::Burn))
		{
			RemoveDebuff(Existing);
		}
	}

	if (HAC->HasTag("Character.DeBuff.Slow"))
	{
		if (!FindDebuffWidget(EStatusEffectType::Slow))
		{
			AddDebuff(EStatusEffectType::Slow);
		}
	}
	else
	{
		if (UYggDebuffUserWidget* Existing = FindDebuffWidget(EStatusEffectType::Slow))
		{
			RemoveDebuff(Existing);
		}
	}

	if (HAC->HasTag("Character.DeBuff.Stunned"))
	{
		if (!FindDebuffWidget(EStatusEffectType::Stunned))
		{
			AddDebuff(EStatusEffectType::Stunned);
		}
	}
	else
	{
		if (UYggDebuffUserWidget* Existing = FindDebuffWidget(EStatusEffectType::Stunned))
		{
			RemoveDebuff(Existing);
		}
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

void UYggStatusEffectUserWidget::AddDebuff(EStatusEffectType StatusEffectType)
{
	UYggDebuffUserWidget* NewDebuff = CreateWidget<UYggDebuffUserWidget>(this, DebuffUserWidgetClass);
	NewDebuff->InitDebuff(StatusEffectType);

	DebuffContainer->AddChild(NewDebuff);
	DebuffWidgets.Add(NewDebuff);
}

void UYggStatusEffectUserWidget::RemoveDebuff(UYggDebuffUserWidget* Debuff)
{
	DebuffContainer->RemoveChild(Debuff);
	DebuffWidgets.Remove(Debuff);
}
