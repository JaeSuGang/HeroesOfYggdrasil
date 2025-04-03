// Coded By AssortRock Unreal Engine Class Project


#include "Upgrade/UpgradeManager.h"

#include "Engine/AssetManager.h"

AUpgradeManager::AUpgradeManager()
{
	bReplicates = true;
	bAlwaysRelevant = true;
	NetDormancy = DORM_Never;
}

AUpgradeManager* AUpgradeManager::Get(UWorld* WorldContext)
{
	return nullptr;
}

void AUpgradeManager::BeginPlay()
{
	Super::BeginPlay();

	// GEngine->AssetManager
}

void AUpgradeManager::Upgrade(UAttributeComponent* AttributeComponent, UUpgradeDataAsset* UpgradeData)
{

}
