#include "Upgrade/UpgradeDataAsset.h"

#include "Upgrade/UpgradeEffects.h"

FPrimaryAssetId UUpgradeDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(TEXT("Upgrade"), Id);
}

