// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggSelectAbilityUserWidget.h"

#include "MainGame/UI/YggAbilityUserWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"

#include "MainGame/MainGamePlayerState.h"

#include "UpgradeSystem/UpgradeSystem.h"
#include "UpgradeSystem/UpgradeDataAsset.h"

void UYggSelectAbilityUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMainGamePlayerState* PS = PC->GetPlayerState<AMainGamePlayerState>();
	
	if (!AbilityUserWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	Ability_0 = CreateWidget<UYggAbilityUserWidget>(GetWorld(), AbilityUserWidgetClass);

	if (IsValid(Ability_0))
	{
		if (IsValid(SelectAbilityPanel))
		{
			SelectAbilityPanel->AddChild(Ability_0);

			if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Ability_0->Slot))
			{
				CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
				CanvasSlot->SetAnchors(FAnchors(0.5f, 0.5f));
				CanvasSlot->SetPosition(FVector2D(-500.0f, 0.0f));
			}
		}
	}
	Ability_0->AbilityInit(PS->AvailableUpgradeIds[0]);

	Ability_1 = CreateWidget<UYggAbilityUserWidget>(GetWorld(), AbilityUserWidgetClass);

	if (IsValid(Ability_1))
	{
		if (IsValid(SelectAbilityPanel))
		{
			SelectAbilityPanel->AddChild(Ability_1);

			if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Ability_1->Slot))
			{
				CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
				CanvasSlot->SetAnchors(FAnchors(0.5f, 0.5f));
				CanvasSlot->SetPosition(FVector2D(0.0f, 0.0f));
			}
		}
	}
	Ability_1->AbilityInit(PS->AvailableUpgradeIds[1]);

	Ability_2 = CreateWidget<UYggAbilityUserWidget>(GetWorld(), AbilityUserWidgetClass);

	if (IsValid(Ability_2))
	{
		if (IsValid(SelectAbilityPanel))
		{
			SelectAbilityPanel->AddChild(Ability_2);

			if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(Ability_2->Slot))
			{
				CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
				CanvasSlot->SetAnchors(FAnchors(0.5f, 0.5f));
				CanvasSlot->SetPosition(FVector2D(500.0f, 0.0f));
			}
		}
	}
	Ability_2->AbilityInit(PS->AvailableUpgradeIds[2]);

	PlayPopupAnim();
}

void UYggSelectAbilityUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (IsValid(ExitButton))
	{
		ExitButton->OnClicked.AddDynamic(this, &UYggSelectAbilityUserWidget::ExitButtonEvent);
	}
}

void UYggSelectAbilityUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

	if (IsValid(ExitButton))
	{
		ExitButton->OnClicked.RemoveDynamic(this, &UYggSelectAbilityUserWidget::ExitButtonEvent);
	}
}

void UYggSelectAbilityUserWidget::ExitButtonEvent()
{
	PlayRPopupAnim();
	//SetVisibility(ESlateVisibility::Hidden);
}

void UYggSelectAbilityUserWidget::PlayPopupAnim()
{
	PlayAnimation(PopupAnim);
}

void UYggSelectAbilityUserWidget::PlayRPopupAnim()
{
	PlayAnimationReverse(PopupAnim);
}
