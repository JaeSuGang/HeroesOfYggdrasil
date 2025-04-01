// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Upgrades.generated.h"

class APlayerController;

/**
 * 담당 코더 : 김경민
 * Server측에서만 존재, 사용하는 객체. Replicated 및 RPC 미지원.
 */
UCLASS(Abstract)
class HEROESOFYGGDRASIL_API UHeroUpgradeBase : public UObject
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void Apply(APlayerController* PC, float fValueToApply);

protected:
	virtual void Apply_Implementation(APlayerController* PC, float fValueToApply);
};

UCLASS(BlueprintType)
class HEROESOFYGGDRASIL_API UHeroUpgrade_Attack: public UHeroUpgradeBase
{
	GENERATED_BODY()

protected:
	void Apply_Implementation(APlayerController* PC, float fValueToApply) override;
};

UCLASS(BlueprintType)
class HEROESOFYGGDRASIL_API UHeroUpgrade_Defense: public UHeroUpgradeBase
{
	GENERATED_BODY()

protected:
	void Apply_Implementation(APlayerController* PC, float fValueToApply) override;
};

UCLASS(BlueprintType)
class HEROESOFYGGDRASIL_API UHeroUpgrade_HP: public UHeroUpgradeBase
{
	GENERATED_BODY()

protected:
	void Apply_Implementation(APlayerController* PC, float fValueToApply) override;
};

UCLASS(BlueprintType)
class HEROESOFYGGDRASIL_API UHeroUpgrade_MoveSpeed: public UHeroUpgradeBase
{
	GENERATED_BODY()

protected:
	void Apply_Implementation(APlayerController* PC, float fValueToApply) override;
};

UCLASS(BlueprintType)
class HEROESOFYGGDRASIL_API UHeroUpgrade_AttackSpeed : public UHeroUpgradeBase
{
	GENERATED_BODY()

protected:
	void Apply_Implementation(APlayerController* PC, float fValueToApply) override;
};
