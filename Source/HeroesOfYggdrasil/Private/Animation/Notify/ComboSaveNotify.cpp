// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/ComboSaveNotify.h"
#include "Player/YggHero.h"
#include "Attribute/HeroAttributeComponent.h"
#include "Data/YggStructData.h"

void UComboSaveNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp || !MeshComp->GetOwner()) return;

    AYggHero* Hero = Cast<AYggHero>(MeshComp->GetOwner());
    if (!Hero) return;

    UHeroAttributeComponent* AttrComp = Hero->GetHeroAttributeComponent();
    if (!AttrComp || !AttrComp->Status) return;

    AttrComp->Status->CurAttackIndex += 1;
    AttrComp->AddTag(TEXT("Character.State.NotAttackable"));

    GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%d"), AttrComp->Status->CurAttackIndex));
}
