// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggStatusUserWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"

#include "Attribute/HeroAttributeComponent.h"
#include "MainGame/UI/YggStatusEffectUserWidget.h"
#include "MainGame/UI/YggNicknameBarUserWidget.h"
#include "Player/YggHero.h"


void UYggStatusUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();



	if (IsValid(ExitButton))
	{
		ExitButton->OnClicked.AddDynamic(this, &UYggStatusUserWidget::EndStatus);
	}

	if (IsValid(AbilityShowButton))
	{
		AbilityShowButton->OnClicked.AddDynamic(this, &UYggStatusUserWidget::ShowAbility);
	}
}

void UYggStatusUserWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UYggStatusUserWidget::NativeDestruct()
{
	Super::NativeDestruct();


}

void UYggStatusUserWidget::StatusInit()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	AYggHero* Hero = PC->GetPawn<AYggHero>();

	HAC = Hero->GetHeroAttributeComponent();

	FVector2D IconSize(64.0f, 64.0f);

	

	//Symbol->SetBrush(MakeBrush());

	if (IsValid(HPBar))
	{
		HPBar->SetPercent(HAC->HP / HAC->MaxHP);
	}

	if (IsValid(Attack))
	{
		Attack->SetText(FText::AsNumber(HAC->AttackPoints));
	}

	if (IsValid(CriticalChance))
	{
		CriticalChance->SetText(FText::AsNumber(HAC->CriticalChance));
	}

	if (IsValid(CriticalDamage))
	{
		CriticalDamage->SetText(FText::AsNumber(HAC->CriticalDamageRate));
	}

	if (IsValid(AttackSpeed))
	{
		AttackSpeed->SetText(FText::AsNumber(HAC->AttackSpeedRate));
	}

	if (IsValid(Defense))
	{
		Defense->SetText(FText::AsNumber(HAC->DefensePoints));
	}

	if (IsValid(HP))
	{
		HP->SetText(FText::AsNumber(HAC->MaxHP));
	}

	if (IsValid(HPRegen))
	{
		HPRegen->SetText(FText::AsNumber(HAC->HPGeneration));
	}
	
}

void UYggStatusUserWidget::EndStatus()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UYggStatusUserWidget::ShowAbility()
{

}

FSlateBrush MakeBrush(UTexture2D* Tex, FVector2D Size, float Brightness = 1.0f)
{
	FSlateBrush Brush;
	Brush.SetResourceObject(Tex);
	Brush.ImageSize = Size;
	Brush.TintColor = FLinearColor(Brightness, Brightness, Brightness, 1.0f);
	Brush.DrawAs = ESlateBrushDrawType::Image;
	return Brush;
}

UTexture2D SetTexture(FName Hero)
{
	UTexture2D* Tex = nullptr;

	if (FName("Greystone") == Hero)
	{
		//Tex = GreystoneSymbol;
	}
}