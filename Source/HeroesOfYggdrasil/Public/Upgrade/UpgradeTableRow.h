// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UpgradeTableRow.generated.h"

class UUpgradeEffectBase;

/**
 * 담당 코더 : 김경민
 */
USTRUCT()
struct FUpgradeTableRow : public FTableRowBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName UpgradeName;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite)
	TArray<UUpgradeEffectBase*> UpgradeEffects;
};
