// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggStatusUserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"
#include "Components/Button.h"

#include "Attribute/HeroAttributeComponent.h"
#include "Attribute/CharacterAttributeComponent.h"
#include "MainGame/UI/YggStatusEffectUserWidget.h"
#include "MainGame/UI/YggNicknameBarUserWidget.h"
#include "MainGame/UI/MainGameHUD.h"
#include "MainGame/UI/YggMainGameUserWidget.h"
#include "MainGame/UI/YggHasAbilityUserWidget.h"
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

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	AYggHero* Hero = PC->GetPawn<AYggHero>();

	if (!Hero)
		return;

	HAC = Hero->GetHeroAttributeComponent();
	
	HAC->ClientDelegate_OnStatusChanged.AddDynamic(this, &UYggStatusUserWidget::UpdateStatus);
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

FSlateBrush UYggStatusUserWidget::MakeBrush(UTexture2D* Tex, FVector2D Size, float Brightness)
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
		float CritDamPercent = (HAC->CriticalDamageRate + 1.f) * 100.f;
		FString String = FString::Printf(TEXT("%.1f%%"), CritDamPercent);

		CriticalDamage->SetText(FText::FromString(String));
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
		int HPGenInt = HAC->HPGeneration;
		FString String = FString::Printf(TEXT("1초당 %d 회복"), HPGenInt);

		HealthRegen->SetText(FText::FromString(String));
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

	if (IsValid(MoveSpeed))
	{
		MoveSpeed->SetText(FText::AsNumber(HAC->MaxMoveSpeed));
	}

}

void UYggStatusUserWidget::UpdateStatus()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	AYggHero* Hero = PC->GetPawn<AYggHero>();

	if (!Hero)
		return;

	HAC = Hero->GetHeroAttributeComponent();

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
		float CritDamPercent = (HAC->CriticalDamageRate + 1.f) * 100.f;
		FString String = FString::Printf(TEXT("%.1f%%"), CritDamPercent);

		CriticalDamage->SetText(FText::FromString(String));
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
		int HPGenInt = HAC->HPGeneration;
		FString String = FString::Printf(TEXT("1초당 %d 회복"), HPGenInt);

		HealthRegen->SetText(FText::FromString(String));
	}

	if (IsValid(HP))
	{
		FText HealthText = FText::Format(FText::FromString("{0} / {1}"), FText::AsNumber(HAC->HP), FText::AsNumber(HAC->MaxHP));

		HP->SetText(HealthText);
	}

	if (IsValid(MoveSpeed))
	{
		MoveSpeed->SetText(FText::AsNumber(HAC->MaxMoveSpeed));
	}
}

void UYggStatusUserWidget::ShowStatus()
{
	SetVisibility(ESlateVisibility::Visible);
	if (PopupAnim)
	{
		PlayAnimation(PopupAnim);
	}
}

void UYggStatusUserWidget::EndStatus()
{
	if (PopupAnim)
	{		
		PlayAnimationReverse(PopupAnim);
	}
	SetVisibility(ESlateVisibility::HitTestInvisible);

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	AMainGameHUD* HUD = PC->GetHUD<AMainGameHUD>();

	HUD->GetMainGameWidget()->GetHasAbilityWidget()->SetVisibility(ESlateVisibility::Hidden);
}

void UYggStatusUserWidget::ShowAbility()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	AMainGameHUD* HUD = PC->GetHUD<AMainGameHUD>();

	if (ESlateVisibility::Visible != HUD->GetMainGameWidget()->GetHasAbilityWidget()->GetVisibility())
	{
		HUD->GetMainGameWidget()->GetHasAbilityWidget()->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		HUD->GetMainGameWidget()->GetHasAbilityWidget()->SetVisibility(ESlateVisibility::Hidden);
	}
}


UTexture2D* UYggStatusUserWidget::SetTexture(FName Hero)
{
	UTexture2D* Texture = nullptr;

	if (FName("Greystone") == Hero)
	{
		Texture = GreystoneSymbol;
		return Texture;
	}

	if (FName("Khaimera") == Hero)
	{
		Texture = KhaimeraSymbol;
		return Texture;
	}

	if (FName("Aurora") == Hero)
	{
		Texture = AuroraSymbol;
		return Texture;
	}

	if (FName("Revenant") == Hero)
	{
		Texture = RevenantSymbol;
		return Texture;
	}

	return Texture;
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
