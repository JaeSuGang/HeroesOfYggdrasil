// Coded By AssortRock Unreal Engine Class Project


#include "Animation/HeroGreystoneAnimInstance.h"
#include "Player/YggHeroGreystone.h"
#include "Attribute/HeroAttributeComponent.h"

void UHeroGreystoneAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	if (Hero == nullptr)
	{
		return;
	}
	Greystone = Cast<AYggHeroGreystone>(Hero);
}

void UHeroGreystoneAnimInstance::NativeUpdateAnimation(float DeltaTime)
{
	Super::NativeUpdateAnimation(DeltaTime);
	if (Greystone == nullptr)
	{
		return;
	}

	//bIsMoveAttackable = Greystone->GetHeroAttribute()->HasTagExact(TEXT("Character.State.MoveAttackable"));
}
