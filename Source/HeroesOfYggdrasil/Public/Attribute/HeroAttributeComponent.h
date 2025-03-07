// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Attribute/AttributeComponent.h"
#include "HeroAttributeComponent.generated.h"

/**
 *	김성훈
 */
UCLASS()
class HEROESOFYGGDRASIL_API UHeroAttributeComponent : public UAttributeComponent
{
	GENERATED_BODY()

protected:

public:
	UPROPERTY(BlueprintReadOnly)
	float Hp;
	UPROPERTY(BlueprintReadOnly)
	float SpeedRate = 2.0f;
	UPROPERTY(BlueprintReadOnly)
	float JumpRate = 1.0f;
};
