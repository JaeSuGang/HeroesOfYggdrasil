#include "UpgradeSystem/UpgradeDataAsset.h"

FPrimaryAssetId UUpgradeDataAsset::GetPrimaryAssetId() const
{
	return FPrimaryAssetId(TEXT("Upgrade"), Id);
}

