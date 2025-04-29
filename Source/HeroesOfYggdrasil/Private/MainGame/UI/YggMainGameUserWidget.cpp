// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggMainGameUserWidget.h"
#include "MainGame/UI/YggPlayerStatusUserWidget.h"
#include "MainGame/UI/YggOrderStatusUserWidget.h"
#include "MainGame/UI/YggAbilityPlusUserWidget.h"
#include "MainGame/UI/YggAbilityUserWidget.h"
#include "MainGame/UI/YggCastingBarUserWidget.h"
#include "MainGame/UI/YggSkillBarUserWidget.h"
#include "MainGame/UI/YggDeathPopupUserWidget.h"
#include "MainGame/UI/YggSelectAbilityUserWidget.h"
#include "MainGame/UI/YggStatusUserWidget.h"
#include "MainGame/UI/YggStatusEffectUserWidget.h"
#include "MainGame/UI/YggFuelBarUserWidget.h"
#include "MainGame/UI/YggVictoryUserWidget.h"
#include "MainGame/UI/YggDefeatedUserWidget.h"
#include "MainGame/UI/YggHasAbilityUserWidget.h"
#include "MainGame/EnemyManager.h"

#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Blueprint/WidgetTree.h"
#include "LevelSequenceActor.h"
#include "LevelSequencePlayer.h"

#include "Player/YggHeroAurora.h"

#include "Attribute/HeroAttributeComponent.h"
#include "UpgradeSystem/UpgradeSystem.h"
#include "UpgradeSystem/UpgradeDataAsset.h"

#include "StageSystem/StageSystem.h"
#include "StageSystem/StageBase.h"
#include "StageSystem/Stages/BattleStage.h"


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
			CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
			CanvasSlot->SetAnchors(FAnchors(0.5f, 0.5f));
			CanvasSlot->SetPosition(FVector2D(0.0f, 300.0f));
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

	StatusWidget = CreateWidget<UYggStatusUserWidget>(GetWorld(), StatusWidgetClass);
	if (!StatusWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	if (IsValid(StatusWidget))
	{
		MainGamePanel->AddChild(StatusWidget);

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(StatusWidget->Slot))
		{
			//CanvasSlot->SetAnchors(FAnchors(0.0f, 0.0f));
			//CanvasSlot->SetOffsets(FMargin(0.0f));
			//CanvasSlot->SetAlignment(FVector2D(0.0f, 0.0f));
			CanvasSlot->SetPosition(FVector2D(-50.0f, 700.0f));
		}
	}
	
	APlayerController* PC = GetOwningPlayer();

	AYggHeroAurora* Aurora = PC->GetPawn<AYggHeroAurora>();

	if (IsValid(Aurora))
	{
		FuelBarWidget = CreateWidget<UYggFuelBarUserWidget>(GetWorld(), FuelBarWidgetClass);
		if (!FuelBarWidgetClass)
			UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

		if (IsValid(FuelBarWidget))
		{
			MainGamePanel->AddChild(FuelBarWidget);

			if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(FuelBarWidget->Slot))
			{
				CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
				CanvasSlot->SetAnchors(FAnchors(0.5f, 0.5f));
				CanvasSlot->SetPosition(FVector2D(300.0f, 0.0f));
			}
		}
	}

	HasAbilityWidget = CreateWidget<UYggHasAbilityUserWidget>(GetWorld(), HasAbilityWidgetClass);
	if (!HasAbilityWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	if (IsValid(HasAbilityWidget))
	{
		MainGamePanel->AddChild(HasAbilityWidget);

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(HasAbilityWidget->Slot))
		{
			//CanvasSlot->SetAnchors(FAnchors(0.0f, 0.0f));
			//CanvasSlot->SetOffsets(FMargin(0.0f));
			//CanvasSlot->SetAlignment(FVector2D(0.0f, 0.0f));
			CanvasSlot->SetPosition(FVector2D(650.0f, 525.0f));
		}
	}
}

void UYggMainGameUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AbilityPlusButton->OnClicked.AddDynamic(this, &UYggMainGameUserWidget::CreateAbility);

	UStageSystem* StageSystem = UStageSystem::Get(GetWorld());
	UpdateWaveCount(StageSystem->GetBattleStage(), StageSystem->CurrentRound);

	StageSystem->OnStageStartedDelegate.AddDynamic(this, &UYggMainGameUserWidget::UpdateWaveCount);

	StageSystem->OnDefeated.AddDynamic(this, &UYggMainGameUserWidget::ChildWidgetHidden);
	StageSystem->OnVictory.AddDynamic(this, &UYggMainGameUserWidget::CreateVictoryWidget);

	StageSystem->LevelSequenceActor->GetSequencePlayer()->OnFinished.AddDynamic(this, &UYggMainGameUserWidget::CreateDefeatedWidget);

}

void UYggMainGameUserWidget::StartAbilityPlus()
{
	AbilityPlusButton->SetVisibility(ESlateVisibility::Visible);
}

void UYggMainGameUserWidget::EndAbilityPlus()
{
	AbilityPlusButton->SetVisibility(ESlateVisibility::Hidden);
}

void UYggMainGameUserWidget::CreateAbility()
{
	if (nullptr != SelectAbilityWidget)
	{
		SelectAbilityWidget->PlayPopupAnim();
		SelectAbilityWidget->SetVisibility(ESlateVisibility::Visible);
		return;
	}

	if (!SelectAbilityUserWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	SelectAbilityWidget = CreateWidget<UYggSelectAbilityUserWidget>(GetWorld(), SelectAbilityUserWidgetClass);

	if (SelectAbilityWidget)
	{
		MainGamePanel->AddChild(SelectAbilityWidget);

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(SelectAbilityWidget->Slot))
		{
			CanvasSlot->SetAnchors(FAnchors(0.0f, 0.0f, 1.0f, 1.0f));
			CanvasSlot->SetOffsets(FMargin(0.0f));
			CanvasSlot->SetAlignment(FVector2D(0.0f, 0.0f));
		}
	}
}

void UYggMainGameUserWidget::DelSelectAbility()
{
	if (SelectAbilityWidget)
	{
		SelectAbilityWidget->RemoveFromParent();
		SelectAbilityWidget = nullptr;
	}
}

void UYggMainGameUserWidget::StatusVisibility()
{
	if (ESlateVisibility::Visible != StatusWidget->GetVisibility())
	{
		StatusWidget->ShowStatus();
	}
	else
	{
		StatusWidget->EndStatus();
		
		if (HasAbilityWidget)
		{
			HasAbilityWidget->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UYggMainGameUserWidget::UpdateWaveCount(UStageBase* NewStage, int NewRound)
{
	UBattleStage* BattleStage = NewStage->StageSystem->GetBattleStage();
	
	FString String = FString::Printf(TEXT("WAVE %d / %d"), NewRound, BattleStage->WaveTableAsArray.Num());

		WaveCount->SetText(FText::FromString(String));
	}
}

void UYggMainGameUserWidget::ChildWidgetHidden(FOnDefeatedParams OnDefeatedParams)
{
	//TArray<UWidget*> children;
	//WidgetTree->GetAllWidgets(children);
	//
	//for (UWidget* widget : children)
	//{
	//	if (widget)
	//	{
	//		widget->SetVisibility(ESlateVisibility::Hidden);
	//	}
	//}

	MainGamePanel->ClearChildren();
}

void UYggMainGameUserWidget::CreateVictoryWidget(FOnVictoryParams OnVictoryParams)
{
	MainGamePanel->ClearChildren();

	VictoryWidget = CreateWidget<UYggVictoryUserWidget>(GetWorld(), VictoryWidgetClass);
	if (!VictoryWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	if (IsValid(VictoryWidget))
	{
		MainGamePanel->AddChild(VictoryWidget);

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(VictoryWidget->Slot))
		{
			CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
			CanvasSlot->SetAnchors(FAnchors(0.5f, 0.5f));
			CanvasSlot->SetPosition(FVector2D(0.0f, 0.0f));
		}
	}
}

void UYggMainGameUserWidget::CreateDefeatedWidget()
{
	DefeatedWidget = CreateWidget<UYggDefeatedUserWidget>(GetWorld(), DefeatedWidgetClass);
	if (!DefeatedWidgetClass)
		UE_LOG(LogTemp, Warning, TEXT("%S (%u) 대상을 블루프린트에서 설정하지 않음"), __FUNCTION__, __LINE__);

	if (IsValid(DefeatedWidget))
	{
		MainGamePanel->AddChild(DefeatedWidget);

		if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(DefeatedWidget->Slot))
		{
			CanvasSlot->SetAlignment(FVector2D(0.5f, 0.5f));
			CanvasSlot->SetAnchors(FAnchors(0.5f, 0.5f));
			CanvasSlot->SetPosition(FVector2D(0.0f, 0.0f));
		}
	}
}
