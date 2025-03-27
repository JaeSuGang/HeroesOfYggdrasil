// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Greystone/GreystoneRollEndNotify.h"
#include "Animation/HeroGreystoneAnimInstance.h"
#include "Player/YggHeroGreystone.h"
#include "Attribute/HeroAttributeComponent.h"

void UGreystoneRollEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(!MeshComp || !MeshComp->GetOwner()) return;
	UHeroGreystoneAnimInstance* AnimInstance = Cast<UHeroGreystoneAnimInstance>(MeshComp->GetAnimInstance());
	if (!AnimInstance) return;

	AnimInstance->bIsRoll = false;
		
	AYggHeroGreystone* Greystone = Cast<AYggHeroGreystone>(MeshComp->GetOwner());
	if (!Greystone) return;

	Greystone->GetHeroAttributeComponent()->RemoveTag(TEXT("Character.State.NotRollable"));
	Greystone->GetHeroAttributeComponent()->RemoveTag(TEXT("Character.State.NotMoveable"));
}
