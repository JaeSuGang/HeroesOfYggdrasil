// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/YggHeroAnimInstance.h"
#include "HeroKhaimeraAnimInstance.generated.h"

/**	김성훈
 *
 */


class AYggHeroKhaimera;


UCLASS()
class HEROESOFYGGDRASIL_API UHeroKhaimeraAnimInstance : public UYggHeroAnimInstance
{
	GENERATED_BODY()

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeThreadSafeUpdateAnimation(float DeltaTime) override;

protected:
	UPROPERTY(BlueprintReadOnly)
	AYggHeroKhaimera* Khaimera;
private:

};
