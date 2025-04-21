// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggStatusUserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"

#include "Attribute/HeroAttributeComponent.h"
#include "MainGame/UI/YggStatusEffectUserWidget.h"
#include "MainGame/UI/YggNicknameBarUserWidget.h"
#include "Core/YggPlayerState.h"
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

	StatusInit();

	SetVisibility(ESlateVisibility::Hidden);
}

void UYggStatusUserWidget::NativeConstruct()
{
	Super::NativeConstruct();


}

void UYggStatusUserWidget::NativeDestruct()
{
	Super::NativeDestruct();


}

//void UYggStatusUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
//{
//	Super::NativeTick(MyGeometry, InDeltaTime);
//
//	if (true == IsDrag)
//	{
//		FVector2D Result = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
//
//		SetRenderTranslation(Result + DragOffset);
//	}
//}

FSlateBrush MakeBrush(UTexture2D* Tex, FVector2D Size, float Brightness = 1.0f)
{
	FSlateBrush Brush;
	Brush.SetResourceObject(Tex);
	Brush.ImageSize = Size;
	Brush.TintColor = FLinearColor(Brightness, Brightness, Brightness, 1.0f);
	Brush.DrawAs = ESlateBrushDrawType::Image;
	return Brush;
}

void UYggStatusUserWidget::StatusInit()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	AYggHero* Hero = PC->GetPawn<AYggHero>();

	if (!Hero)
		return;

	HAC = Hero->GetHeroAttributeComponent();

	FVector2D IconSize(64.0f, 64.0f);

	if (IsValid(Symbol))
	{
		FName Name = HAC->GetName();
		Symbol->SetBrush(MakeBrush(SetTexture(Name), IconSize, 1.0f));
	}

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
		float CritPercent = HAC->CriticalChance * 100.f;
		FString String = FString::Printf(TEXT("%.1f%%"), CritPercent);

		CriticalChance->SetText(FText::FromString(String));
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

	if (IsValid(Health))
	{
		Health->SetText(FText::AsNumber(HAC->MaxHP));
	}

	if (IsValid(HealthRegen))
	{
		HealthRegen->SetText(FText::AsNumber(HAC->HPGeneration));
	}
	
	if (IsValid(HP))
	{
		FText HealthText = FText::Format(FText::FromString("{0} / {1}"), FText::AsNumber(HAC->HP), FText::AsNumber(HAC->MaxHP));

		HP->SetText(HealthText);
	}

	if (IsValid(Nickname))
	{
		AYggPlayerState* PS = Hero->GetPlayerState<AYggPlayerState>();

		if (nullptr == PS)
		{
			UE_LOG(LogTemp, Error, TEXT("%S(%u)> if (nullptr == PS)"), __FUNCTION__, __LINE__);
			return;
		}

		FString Name = PS->GetPlayerName();

		Nickname->SetText(FText::FromString(Name));
	}

}

void UYggStatusUserWidget::ShowStatus()
{
	SetVisibility(ESlateVisibility::Visible);
}

void UYggStatusUserWidget::EndStatus()
{
	SetVisibility(ESlateVisibility::Hidden);
}

void UYggStatusUserWidget::ShowAbility()
{

}


UTexture2D* UYggStatusUserWidget::SetTexture(FName Hero)
{
	UTexture2D* Tex = nullptr;

	if (FName("Greystone") == Hero)
	{
		Tex = GreystoneSymbol;
		return Tex;
	}

	if (FName("Khaimera") == Hero)
	{
		Tex = KhaimeraSymbol;
		return Tex;
	}

	if (FName("Aurora") == Hero)
	{
		Tex = AuroraSymbol;
		return Tex;
	}

	if (FName("Revenant") == Hero)
	{
		Tex = RevenantSymbol;
		return Tex;
	}

	return Tex;
}

//void UYggStatusUserWidget::DragStart()
//{
//	IsDrag = true;
//
//	FVector2D Result = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
//
//	DragOffset = GetRenderTransform().Translation - Result;
//
//	SetRenderTranslation(DragOffset + Result);
//}

//void UYggStatusUserWidget::DragEnd()
//{
//	IsDrag = false;
//}
