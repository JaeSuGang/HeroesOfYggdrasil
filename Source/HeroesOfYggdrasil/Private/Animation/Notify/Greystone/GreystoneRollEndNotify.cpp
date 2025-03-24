// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Greystone/GreystoneRollEndNotify.h"
#include "Animation/HeroGreystoneAnimInstance.h"

void UGreystoneRollEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	UHeroGreystoneAnimInstance* AnimInstance = Cast<UHeroGreystoneAnimInstance>(MeshComp->GetAnimInstance());
	if (!AnimInstance) return;

	AnimInstance->bIsRoll = false;
}
