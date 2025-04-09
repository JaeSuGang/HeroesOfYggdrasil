// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Hero/HeroAnimNotifySkillStart.h"
#include "Player/YggHero.h"
#include "Attribute/HeroAttributeComponent.h"


void UHeroAnimNotifySkillStart::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp || !MeshComp->GetOwner()) return;

    AYggHero* Hero = Cast<AYggHero>(MeshComp->GetOwner());

    if (!Hero) return;

    Hero->GetHeroAttributeComponent()->AddTag(TEXT("Character.State.NotMoveable"));
    Hero->GetHeroAttributeComponent()->AddTag(TEXT("Character.State.NotAttackable"));
}
