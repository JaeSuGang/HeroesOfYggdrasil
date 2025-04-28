// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "UpgradeDataAsset.generated.h"

class UTexture2D;
class UUpgradeEffectBase;

UENUM(BlueprintType)
enum class EUpgradeRarity : uint8
{
	Common UMETA(DisplayName = "노말"),
	Epic UMETA(DisplayName = "에픽"),
	Legendary UMETA(DisplayName = "레전더리")
};

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
	EUpgradeRarity Rarity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName UpgradeName;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName UpgradeDescription;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UTexture2D* UpgradeImage;

	UPROPERTY(Instanced, EditAnywhere, BlueprintReadWrite)
	TArray<UUpgradeEffectBase*> UpgradeEffects;
};