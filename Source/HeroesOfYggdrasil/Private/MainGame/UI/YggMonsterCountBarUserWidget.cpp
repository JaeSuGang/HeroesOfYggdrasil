// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggMonsterCountBarUserWidget.h"

#include "Components/TextBlock.h"

#include "MainGame/EnemyManager.h"

void UYggMonsterCountBarUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();

}

void UYggMonsterCountBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MonsterCount->SetText(FText::AsNumber(0));

	AEnemyManager* EManager = AEnemyManager::Get(GetWorld());

	if (!IsValid(EManager)) return;

	EManager->OnEnemyCountDelegate.AddDynamic(this, &UYggMonsterCountBarUserWidget::UpdateWidget);
}

void UYggMonsterCountBarUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UYggMonsterCountBarUserWidget::UpdateWidget(AEnemyManager* EnemyManager)
{
	if (IsValid(EnemyManager))
	{
		FString String = FString::Printf(TEXT("%d"), EnemyManager->AllEnemyCharacter.Num());

		MonsterCount->SetText(FText::FromString(String));
	}
	else
	{
		FString String = FString::Printf(TEXT("%d"), EnemyManager->AllEnemyCharacter.Num());

		MonsterCount->SetText(FText::FromString(String));
	}
}