// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/YggHeroAnimInstance.h"
#include "HeroGreystoneAnimInstance.generated.h"


class AYggHeroGreystone;

UCLASS()
class HEROESOFYGGDRASIL_API UHeroGreystoneAnimInstance : public UYggHeroAnimInstance
{
	GENERATED_BODY()

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTime) override;


protected:
	UPROPERTY(BlueprintReadOnly)
	AYggHeroGreystone* Greystone;

	UPROPERTY(BlueprintReadOnly)
	bool bIsMoveAttackable = false;
};
