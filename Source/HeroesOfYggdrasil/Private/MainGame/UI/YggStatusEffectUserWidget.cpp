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
	UCharacterAttributeComponent* HAC = Hero->GetAttributeComponent();

	if (HAC->HasTag("Character.DeBuff.Poison") || !FindDebuffWidget(EStatusEffectType::Poison))
	{
		//if (UYggDebuffUserWidget* Existing = FindDebuffWidget(EStatusEffectType::Poison))
		//{
		//	DebuffContainer->RemoveChild(Existing);
		//	DebuffWidgets.Remove(Existing);
		//}
		//if (FindDebuffWidget(EStatusEffectType::Poison))
		//	return;

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
	
	if (HAC->HasTag("Character.DeBuff.Burn") || !FindDebuffWidget(EStatusEffectType::Burn))
	{
		//if (FindDebuffWidget(EStatusEffectType::Burn))
		//	return;

		UYggDebuffUserWidget* NewDebuff = CreateWidget<UYggDebuffUserWidget>(this, DebuffUserWidgetClass);
		NewDebuff->InitDebuff(EStatusEffectType::Burn);

		DebuffContainer->AddChild(NewDebuff);
		DebuffWidgets.Add(NewDebuff);
	}
	else if (UYggDebuffUserWidget* Existing = FindDebuffWidget(EStatusEffectType::Burn))
	{
		DebuffContainer->RemoveChild(Existing);
		DebuffWidgets.Remove(Existing);
	}
	
	if (HAC->HasTag("Character.DeBuff.Slow") || !!FindDebuffWidget(EStatusEffectType::Slow))
	{
		//if (FindDebuffWidget(EStatusEffectType::Slow))
		//	return;

		UYggDebuffUserWidget* NewDebuff = CreateWidget<UYggDebuffUserWidget>(this, DebuffUserWidgetClass);
		NewDebuff->InitDebuff(EStatusEffectType::Slow);

		DebuffContainer->AddChild(NewDebuff);
		DebuffWidgets.Add(NewDebuff);
	}
	else if (UYggDebuffUserWidget* Existing = FindDebuffWidget(EStatusEffectType::Slow))
	{
		DebuffContainer->RemoveChild(Existing);
		DebuffWidgets.Remove(Existing);
	}

	if (HAC->HasTag("Character.DeBuff.Stunned") || !FindDebuffWidget(EStatusEffectType::Stunned))
	{
		//if (FindDebuffWidget(EStatusEffectType::Stunned))
		//	return;

		UYggDebuffUserWidget* NewDebuff = CreateWidget<UYggDebuffUserWidget>(this, DebuffUserWidgetClass);
		NewDebuff->InitDebuff(EStatusEffectType::Stunned);

		DebuffContainer->AddChild(NewDebuff);
		DebuffWidgets.Add(NewDebuff);
	}
	else if (UYggDebuffUserWidget* Existing = FindDebuffWidget(EStatusEffectType::Stunned))
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
