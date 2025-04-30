// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggHasAbilityUserWidget.h"
#include "MainGame/UI/MainGameHUD.h"
#include "MainGame/UI/YggTooltipUserWidget.h"

#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"


void UYggHasAbilityUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetVisibility(ESlateVisibility::Hidden);

	if (IsValid(ExitButton))
	{
		ExitButton->OnClicked.AddDynamic(this, &UYggHasAbilityUserWidget::EndHasAbility);
	}
}

void UYggHasAbilityUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Abilitys.Add(Ability0);
	Abilitys.Add(Ability1);
	Abilitys.Add(Ability2);
	Abilitys.Add(Ability3);
	Abilitys.Add(Ability4);
	Abilitys.Add(Ability5);
	Abilitys.Add(Ability6);
	Abilitys.Add(Ability7);
	Abilitys.Add(Ability8);
	Abilitys.Add(Ability9);

	AbilityButtons.Add(AbilityButton0);
	AbilityButtons.Add(AbilityButton1);
	AbilityButtons.Add(AbilityButton2);
	AbilityButtons.Add(AbilityButton3);
	AbilityButtons.Add(AbilityButton4);
	AbilityButtons.Add(AbilityButton5);
	AbilityButtons.Add(AbilityButton6);
	AbilityButtons.Add(AbilityButton7);
	AbilityButtons.Add(AbilityButton8);
	AbilityButtons.Add(AbilityButton9);

	for (int32 i = 0; i < AbilityButtons.Num(); i++)
	{
		AbilityButtons[i]->OnHovered.AddDynamic(this, &UYggHasAbilityUserWidget::OnHovered);
		AbilityButtons[i]->OnUnhovered.AddDynamic(this, &UYggHasAbilityUserWidget::OnUnHovered);

		ButtonIndexMap.Add(AbilityButtons[i], i);
	}

	UpdateWidget();
}

void UYggHasAbilityUserWidget::NativeDestruct()
{
	Super::NativeDestruct();


}

void UYggHasAbilityUserWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (CurTooltipWidget)
	{
		FVector2D MousePosition;
		if (GetWorld()->GetFirstPlayerController()->GetMousePosition(MousePosition.X, MousePosition.Y))
		{
			FVector2D Offset(20.f, 20.f);
			CurTooltipWidget->SetPositionInViewport(MousePosition + Offset, true);
		}
	}
}

void UYggHasAbilityUserWidget::EndHasAbility()
{
	SetVisibility(ESlateVisibility::Hidden);

	if (ClickSound)
	{
		UGameplayStatics::PlaySound2D(this, ClickSound, 0.1f);
	}
}

void UYggHasAbilityUserWidget::UpdateWidget()
{
	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	AMainGameHUD* HUD = PC->GetHUD<AMainGameHUD>();

	const TArray<FName>& HasAbilityName = HUD->GetHasAbilityName();

	const TMap<FName, FHasAbilityInfo>& HasAbilityInfo = HUD->GetHasAbilityInfo();

	for (int32 i = 0; i < Abilitys.Num(); i++)
	{
		if (Abilitys[i] && HasAbilityName.IsValidIndex(i))
		{
			if (const FHasAbilityInfo* Info = HasAbilityInfo.Find(HasAbilityName[i]))
			{
				if (Info->Texture)
				{
					Abilitys[i]->SetBrushFromTexture(Info->Texture);
					AbilityButtons[i]->SetVisibility(ESlateVisibility::Visible);
				}
			}
		}
		else if (Abilitys[i])
		{
			Abilitys[i]->SetBrushFromTexture(nullptr);
			AbilityButtons[i]->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UYggHasAbilityUserWidget::OnHovered()
{
	if (!TooltipWidgetClass)
	{
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);
		return;
	}
	
	CurTooltipWidget = CreateWidget<UYggTooltipUserWidget>(GetWorld(), TooltipWidgetClass);
	
	if (CurTooltipWidget)
	{
		CurTooltipWidget->AddToViewport();
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();

	AMainGameHUD* HUD = PC->GetHUD<AMainGameHUD>();

	for (const auto& Pair : ButtonIndexMap)
	{
		if (Pair.Key && Pair.Key->IsHovered())
		{
			CurrentHoveredIndex = Pair.Value;

			const TArray<FName>& AbilityNames = HUD->GetHasAbilityName();
			const TMap<FName, FHasAbilityInfo>& AbilityInfos = HUD->GetHasAbilityInfo();

			if (AbilityNames.IsValidIndex(CurrentHoveredIndex))
			{
				const FName& AbilityName = AbilityNames[CurrentHoveredIndex];
				if (const FHasAbilityInfo* Info = AbilityInfos.Find(AbilityName))
				{
					CurTooltipWidget->SetTipText(FText::FromName(AbilityName), FText::FromName(Info->Description));
				}
			}
			break;
		}
	}
}

void UYggHasAbilityUserWidget::OnUnHovered()
{
	if (CurTooltipWidget)
	{
		CurTooltipWidget->RemoveFromParent();
		CurTooltipWidget = nullptr;
	}
}
