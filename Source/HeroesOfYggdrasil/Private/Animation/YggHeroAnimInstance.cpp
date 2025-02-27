// Coded By AssortRock Unreal Engine Class Project


#include "Animation/YggHeroAnimInstance.h"

#include "Player/YggHero.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


void UYggHeroAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Hero = Cast<AYggHero>(TryGetPawnOwner());
	if (Hero == nullptr)
	{
		return;
	}
	CharacterMovementComponent = Hero->GetCharacterMovement();
	
}

void UYggHeroAnimInstance::NativeUpdateAnimation(float _DeltaTime)
{
	Super::NativeUpdateAnimation(_DeltaTime);
	if (CharacterMovementComponent == nullptr)
	{
		return;
	}
}

