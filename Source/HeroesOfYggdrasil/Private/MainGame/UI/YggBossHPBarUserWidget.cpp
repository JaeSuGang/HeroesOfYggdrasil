// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggBossHPBarUserWidget.h"

#include "MainGame/EnemyManager.h"
#include "StageSystem/StageSystem.h"

#include "Enemy/EnemyCharacter.h"
#include "Attribute/CharacterAttributeComponent.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"



void UYggBossHPBarUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

	SetVisibility(ESlateVisibility::Hidden);
}

void UYggBossHPBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	AEnemyManager* EnemyManager = AEnemyManager::Get(GetWorld());

	EnemyManager->OnEnemyCountDelegate.AddDynamic(this, &UYggBossHPBarUserWidget::Init);
}

void UYggBossHPBarUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UYggBossHPBarUserWidget::UpdateWidget()
{
	
	if (IsValid(HPBar) && IsValid(HPText))
	{
		float Percent = CAC->HP / CAC->MaxHP;
		FText HealthText = FText::Format(FText::FromString("{0} / {1}"), FText::AsNumber(CAC->HP), FText::AsNumber(CAC->MaxHP));

		if (0 >= Percent)
		{
			SetVisibility(ESlateVisibility::Hidden);
		}

		HPBar->SetPercent(Percent);
		HPText->SetText(HealthText);
	}
}

void UYggBossHPBarUserWidget::Init(AEnemyManager* EnemyManager)
{
	UStageSystem* StageSystem = UStageSystem::Get(GetWorld());
	
	if (!IsValid(StageSystem) || !IsValid(EnemyManager))
		return;

	if (IsValid(CAC))
		return;

	if (!(5 == StageSystem->CurrentRound || 10 == StageSystem->CurrentRound))
	{
		CAC = nullptr;
		if (ESlateVisibility::Visible == GetVisibility())
		{
			SetVisibility(ESlateVisibility::Hidden);
		}
		return;
	}

	for (AEnemyCharacter* Enemy : EnemyManager->AllEnemyCharacter)
	{
		if (!IsValid(Enemy))
			continue;

		FString EnemyName = Enemy->GetDataKey();

		if (EnemyName.Contains(TEXT("Dragon"), ESearchCase::IgnoreCase))
		{
			CAC = Enemy->GetAttributeComponent();
			CAC->ClientDelegate_OnStatusChanged.RemoveDynamic(this, &UYggBossHPBarUserWidget::UpdateWidget);
			CAC->ClientDelegate_OnStatusChanged.AddDynamic(this, &UYggBossHPBarUserWidget::UpdateWidget);
			SetVisibility(ESlateVisibility::Visible);
			UpdateWidget();
			break;
		}
	}
}
