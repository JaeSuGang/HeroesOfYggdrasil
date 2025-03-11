// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Greystone/GreystoneRLand.h"
#include "Interfaces/YggHeroInterface.h"
#include "Player/YggHeroGreystone.h"
#include "Attribute/HeroAttributeComponent.h"

void UGreystoneRLand::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp || !MeshComp->GetOwner()) return;

    AYggHeroGreystone* GreystoneCharacter = Cast<AYggHeroGreystone>(MeshComp->GetOwner());
    if (GreystoneCharacter && GreystoneCharacter->GetClass()->ImplementsInterface(UYggHeroInterface::StaticClass()))
    {
        GreystoneCharacter->GetHeroAttributeComponent()->RemoveTag(TEXT("Character.State.NotMoveable"));
        GreystoneCharacter->GetHeroAttributeComponent()->RemoveTag(TEXT("Character.State.NotAttackable"));
    }
}
