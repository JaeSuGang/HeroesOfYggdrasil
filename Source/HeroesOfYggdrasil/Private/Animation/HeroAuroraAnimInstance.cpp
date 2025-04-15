// Coded By AssortRock Unreal Engine Class Project


#include "Animation/HeroAuroraAnimInstance.h"
#include "Player/YggHeroAurora.h"

void UHeroAuroraAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (Hero == nullptr)
	{
		return;
	}
	Aurora = Cast<AYggHeroAurora>(Hero);
}

void UHeroAuroraAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (Aurora == nullptr)
	{
		return;
	}
}