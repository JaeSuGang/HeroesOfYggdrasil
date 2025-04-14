// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UpgradeDataAsset.generated.h"

class UTexture2D;
class UUpgradeEffectBase;

/**
 * 담당 코더 : 김경민
 */
UCLASS(BlueprintType)
class HEROESOFYGGDRASIL_API UUpgradeDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Id;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName UpgradeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName UpgradeDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* UpgradeImage;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite)
	TArray<UUpgradeEffectBase*> UpgradeEffects;
};