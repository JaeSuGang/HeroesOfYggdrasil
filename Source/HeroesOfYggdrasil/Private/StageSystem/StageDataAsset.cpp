// Coded By AssortRock Unreal Engine Class Project


#include "StageSystem/StageDataAsset.h"

FPrimaryAssetId UStageDataAsset::GetPrimaryAssetId() const
{
    return FPrimaryAssetId(TEXT("Stage"), GetFName());
}
