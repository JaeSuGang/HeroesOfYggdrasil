// Coded By AssortRock Unreal Engine Class Project


#include "Animation/YggHeroAnimInstance.h"

#include "Player/YggHero.h"
#include "GameFramework/CharacterMovementComponent.h"


void UYggHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Hero = Cast<AYggHero>(TryGetPawnOwner());
	if (Hero == nullptr)
	{
		return;
	}
	MovementComponent = Hero->GetCharacterMovement();
}

void UYggHeroAnimInstance::NativeUpdateAnimation(float _DeltaTime)
{
	Super::NativeUpdateAnimation(_DeltaTime);
	if (MovementComponent == nullptr)
	{
		return;
	}
}
