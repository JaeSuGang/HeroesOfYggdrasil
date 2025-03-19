// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Hero/SkillEndNotify.h"
#include "Player/YggHero.h"
#include "Attribute/HeroAttributeComponent.h"

void USkillEndNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp || !MeshComp->GetOwner()) return;

	AYggHero* Hero = Cast<AYggHero>(MeshComp->GetOwner());

    if (!Hero) return;
      
    Hero->GetHeroAttributeComponent()->RemoveTag(TEXT("Character.State.NotMoveable"));
    Hero->GetHeroAttributeComponent()->RemoveTag(TEXT("Character.State.NotAttackable"));
}
