// Coded By AssortRock Unreal Engine Class Project


#include "MainGame/UI/YggBossHPBarUserWidget.h"

#include "MainGame/EnemyManager.h"
#include "StageSystem/StageSystem.h"

#include "Enemy/EnemyCharacter.h"
#include "Attribute/CharacterAttributeComponent.h"



void UYggBossHPBarUserWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();


}

void UYggBossHPBarUserWidget::NativeConstruct()
{
	Super::NativeConstruct();

	UStageSystem* StageSystem = UStageSystem::Get(GetWorld());

	StageSystem->OnStageStartedDelegate.AddDynamic(this, UYggBossHPBarUserWidget::Init);
}

void UYggBossHPBarUserWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UYggBossHPBarUserWidget::UpdateWidget()
{

}

void UYggBossHPBarUserWidget::Init(UStageBase* NewStage)
{
	AEnemyManager* EnemyManager = AEnemyManager::Get(GetWorld());

	for (AEnemyCharacter* Enemy : EnemyManager->AllEnemyCharacter)
	{
		if (!IsValid(Enemy))
			return;

		FString EnemyName = Enemy->GetDataKey();

		if (EnemyName.Contains(TEXT("Dragon"), ESearchCase::IgnoreCase))
		{
			CAC = Enemy->GetAttributeComponent();
		}
	}
}
