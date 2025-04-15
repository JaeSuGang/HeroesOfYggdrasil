// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/YggHeroAnimInstance.h"
#include "HeroAuroraAnimInstance.generated.h"

/**
 * 
 */
class AYggHeroAurora;

UCLASS()
class HEROESOFYGGDRASIL_API UHeroAuroraAnimInstance : public UYggHeroAnimInstance
{
	GENERATED_BODY()

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	AYggHeroAurora* Aurora;

};
