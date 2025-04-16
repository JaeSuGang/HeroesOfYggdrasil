// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UpgradeSystem/UpgradeEffectBase.h"
#include "UpgradeEffects.generated.h"

class UHeroAttributeComponent;

/**
 * 담당 코더 : 김경민
 * 스탯을 증가시키는 효과
 */
UCLASS(Blueprintable)
class HEROESOFYGGDRASIL_API UUpgradeEffect_Stats : public UUpgradeEffectBase
{
	GENERATED_BODY()
	
public:
	virtual void ApplyInternal_Implementation(UAttributeComponent* TargetAttribute) override;

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float HPGeneration;
};

UCLASS(Blueprintable)
class HEROESOFYGGDRASIL_API UUpgradeEffect_TeamStats : public UUpgradeEffect_Stats
{
	GENERATED_BODY()

public:
	virtual void ApplyInternal_Implementation(UAttributeComponent* TargetAttribute) override;
};

UCLASS(Blueprintable)
class HEROESOFYGGDRASIL_API UUpgradeEffect_World: public UUpgradeEffectBase
{
	GENERATED_BODY()

public:
	virtual void ApplyInternal_Implementation(UAttributeComponent* TargetAttribute) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHealAllPlayers;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bHealYggdrasil;
};