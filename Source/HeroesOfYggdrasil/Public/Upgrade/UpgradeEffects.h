// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Upgrade/UpgradeEffectBase.h"
#include "UpgradeEffects.generated.h"

/**
 * 담당 코더 : 김경민
 * 스탯을 증가시키는 효과
 */
UCLASS(BlueprintType)
class HEROESOFYGGDRASIL_API UUpgradeEffect_Stats : public UUpgradeEffectBase
{
	GENERATED_BODY()
	

public:
	virtual void Apply_Implementation() override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackIncrement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float DefenseIncrement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HPIncrement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveSpeedIncrement;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float AttackSpeedIncrement;
};
