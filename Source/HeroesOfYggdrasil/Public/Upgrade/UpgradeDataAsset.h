// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UpgradeDataAsset.generated.h"

class UTexture;
class UUpgradeEffectBase;

/**
 * 담당 코더 : 김경민
 */

/*
* 
*/
UCLASS(BlueprintType)
class HEROESOFYGGDRASIL_API UUpgradeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName UpgradeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName UpgradeDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture* UpgradeImage;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite)
	TArray<UUpgradeEffectBase*> UpgradeEffects;
};


USTRUCT(BlueprintType)
struct HEROESOFYGGDRASIL_API FUpgradeDataTableRow : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSoftObjectPtr<UUpgradeDataAsset> UpgradeDataAsset;
};
