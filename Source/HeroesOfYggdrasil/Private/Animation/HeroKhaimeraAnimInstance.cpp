// Coded By AssortRock Unreal Engine Class Project


#include "Animation/HeroKhaimeraAnimInstance.h"
#include "Player/YggHeroKhaimera.h"
#include "Attribute/HeroAttributeComponent.h"

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
	if (Khaimera == nullptr) 
	{ 
		return; 
	}
	bIsMoveAttackable = Khaimera->GetHeroAttribute()->HasTagExact(TEXT("Character.State.MoveAttackable"));
}
