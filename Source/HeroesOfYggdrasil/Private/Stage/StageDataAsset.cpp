// Coded By AssortRock Unreal Engine Class Project


#include "Stage/StageDataAsset.h"

FPrimaryAssetId UStageDataAsset::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(TEXT("Stage"), Id);
}
