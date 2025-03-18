// Coded By AssortRock Unreal Engine Class Project

#include "Animation/Notify/ComboResetNotify.h"
#include "Player/YggHero.h"
#include "Attribute/HeroAttributeComponent.h"
#include "Data/YggStructData.h"

void UComboResetNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp || !MeshComp->GetOwner()) return;

    AYggHero* Hero = Cast<AYggHero>(MeshComp->GetOwner());
    if (!Hero) return;

    UHeroAttributeComponent* AttrComp = Hero->GetHeroAttributeComponent();
    if (!AttrComp) return;

    AttrComp->ResetComboAttack();
    AttrComp->RemoveTag(TEXT("Character.State.NotAttackable"));

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, TEXT("Combo Reset"));
}