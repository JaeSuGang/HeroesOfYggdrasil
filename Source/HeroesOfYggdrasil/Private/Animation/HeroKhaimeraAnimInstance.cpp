// Coded By AssortRock Unreal Engine Class Project


#include "Animation/HeroKhaimeraAnimInstance.h"
#include "Player/YggHeroKhaimera.h"

void UHeroKhaimeraAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (Hero == nullptr)
	{
		return;
	}
	Khaimera = Cast<AYggHeroKhaimera>(Hero);
}

void UHeroKhaimeraAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
}
