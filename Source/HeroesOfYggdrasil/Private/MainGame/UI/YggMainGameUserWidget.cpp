// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggMainGameUserWidget.h"
#include "MainGame/UI/YggPlayerStatusUserWidget.h"
#include "MainGame/UI/YggOrderStatusUserWidget.h"
#include "MainGame/UI/YggAbilityPlusUserWidget.h"
#include "MainGame/UI/YggAbilityUserWidget.h"
#include "MainGame/UI/YggCastingBarUserWidget.h"
#include "MainGame/UI/YggSkillBarUserWidget.h"
#include "MainGame/UI/YggDeathPopupUserWidget.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"


void UYggMainGameUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	PlayerStatusWidget = CreateWidget<UYggPlayerStatusUserWidget>(GetWorld(), PlayerStatusUserWidgetClass);
	if (!PlayerStatusUserWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	if (IsValid(PlayerStatusWidget))
	{
		MainGamePanel->AddChild(PlayerStatusWidget);

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(PlayerStatusWidget->Slot))
		{
			CanvasSlot->SetAlignment(FVector2D(0.0f, 0.0f));
			CanvasSlot->SetAnchors(FAnchors(0.0f, 0.0f));
			CanvasSlot->SetPosition(FVector2D(10.0f, 10.0f));
		}
	}

	if (!OrderStatusUserWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	CastingBarWidget = CreateWidget<UYggCastingBarUserWidget>(GetWorld(), CastingBarUserWidgetClass);
	if (!CastingBarUserWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	if (IsValid(CastingBarWidget))
	{
		MainGamePanel->AddChild(CastingBarWidget);

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(CastingBarWidget->Slot))
		{
			//CanvasSlot->SetAlignment(FVector2D(0.0f, 0.0f));
			//CanvasSlot->SetAnchors(FAnchors(0.0f, 0.0f));
			CanvasSlot->SetPosition(FVector2D(850.0f, 850.0f));
		}
	}

	SkillBarWidget = CreateWidget<UYggSkillBarUserWidget>(GetWorld(), SkillBarUserWidgetClass);
	if (!SkillBarUserWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	if (IsValid(SkillBarWidget))
	{
		MainGamePanel->AddChild(SkillBarWidget);

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SkillBarWidget->Slot))
		{
			CanvasSlot->SetAnchors(FAnchors(0.5f, 1.0f));
			CanvasSlot->SetAlignment(FVector2D(0.0f, 0.0f));
			CanvasSlot->SetPosition(FVector2D(-296.0f, -183.0f));
			
		}
	}

	DeathPopupWidget = CreateWidget<UYggDeathPopupUserWidget>(GetWorld(), DeathPopupWidgetClass);
	if (!DeathPopupWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	if (IsValid(DeathPopupWidget))
	{
		MainGamePanel->AddChild(DeathPopupWidget);

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(DeathPopupWidget->Slot))
		{
			CanvasSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
			CanvasSlot->SetOffsets(FMargin(0.0f));
			CanvasSlot->SetAlignment(FVector2D(0.0f, 0.0f));
		}
	}

	if (!AbilityPlusUserWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	AbilityPlusWidget = CreateWidget<UYggAbilityPlusUserWidget>(GetWorld(), AbilityPlusUserWidgetClass);

	if (AbilityPlusWidget)
	{
		MainGamePanel->AddChild(AbilityPlusWidget);

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(AbilityPlusWidget->Slot))
		{
			CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
			CanvasSlot->SetAnchors(FAnchors(0.5f, 0.5f));
			CanvasSlot->SetPosition(FVector2D(500.0f, 500.0f));
		}
	}

	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	AMainGamePlayerState* PS = PC->GetPlayerState<AMainGamePlayerState>();

	//PS->OnUpgradePointsChanged.AddDynamic(this, &UYggMainGameUserWidget::OnUpgradePointChange);
}

//void UYggMainGameUserWidget::CreateAbilityPlus()
//{
//	if (!AbilityPlusUserWidgetClass)
//		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);
//
//	AbilityPlusWidget = CreateWidget<UYggAbilityPlusUserWidget>(GetWorld(), AbilityPlusUserWidgetClass);
//
//	if (AbilityPlusWidget)
//	{
//		MainGamePanel->AddChild(AbilityPlusWidget);
//
//		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(AbilityPlusWidget->Slot))
//		{
//			CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
//			CanvasSlot->SetAnchors(FAnchors(0.5f, 0.5f));
//			CanvasSlot->SetPosition(FVector2D(500.0f, 500.0f));
//		}
//	}
//}

void UYggMainGameUserWidget::StartAbilityPlus()
{
	AbilityPlusWidget->SetVisibility(ESlateVisibility::Visible);
}

void UYggMainGameUserWidget::EndAbilityPlus()
{
	AbilityPlusWidget->SetVisibility(ESlateVisibility::Hidden);
}

//void UYggMainGameUserWidget::OnUpgradePointChange(FOnUpgradePointsChangedParams OnUpgradePointsChangedParams)
//{
//	if (0 < OnUpgradePointsChangedParams.NewUpgradePoints)
//	{
//		CreateAbilityPlus();
//	}
//	else
//	{
//
//	}
//	
//}

void UYggMainGameUserWidget::CreateAbility()
{
	if (!AbiltyUserWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	AbilityWidget = CreateWidget<UYggAbilityUserWidget>(GetWorld(), AbiltyUserWidgetClass);

	if (AbilityWidget)
	{
		MainGamePanel->AddChild(AbilityWidget);

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(AbilityWidget->Slot))
		{
			CanvasSlot->SetAlignment(FVector2D(0.0f, 0.0f));
			CanvasSlot->SetAnchors(FAnchors(0.5f, 0.5f));
			CanvasSlot->SetPosition(FVector2D(0.0f, 0.0f));
		}
	}
}

void UYggMainGameUserWidget::DelAbilityPlus()
{
	if (AbilityPlusWidget)
	{
		AbilityPlusWidget->RemoveFromParent();
		AbilityPlusWidget = nullptr;
	}
}

void UYggMainGameUserWidget::DelAbility()
{
	if (AbilityWidget)
	{
		AbilityWidget->RemoveFromParent();
		AbilityWidget = nullptr;
	}
}
