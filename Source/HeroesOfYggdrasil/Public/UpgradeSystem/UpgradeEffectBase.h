// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "UpgradeEffectBase.generated.h"

class UAttributeComponent;

/**
 * 담당 코더 : 김경민
 */
UCLASS(EditInlineNew, BlueprintType)
class HEROESOFYGGDRASIL_API UUpgradeEffectBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ApplyInternal(UAttributeComponent* TargetAttribute);
	virtual void ApplyInternal_Implementation(UAttributeComponent* TargetAttribute);
};
