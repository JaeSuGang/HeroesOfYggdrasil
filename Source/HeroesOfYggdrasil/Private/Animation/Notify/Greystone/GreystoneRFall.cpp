// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Greystone/GreystoneRFall.h"
#include "Interfaces/YggHeroInterface.h"
#include "Player/YggHeroGreystone.h"
#include "Attribute/HeroAttributeComponent.h"

void UGreystoneRFall::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp || !MeshComp->GetOwner()) return;
       
    if (auto* AnimInstance = MeshComp->GetAnimInstance())
    {
        UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();

        AnimInstance->Montage_Resume(CurrentMontage);
    }
    
    AYggHeroGreystone* GreystoneCharacter = Cast<AYggHeroGreystone>(MeshComp->GetOwner());
    if (GreystoneCharacter && GreystoneCharacter->GetClass()->ImplementsInterface(UYggHeroInterface::StaticClass()))
    {
        GreystoneCharacter->MagicCircleOff();

        GreystoneCharacter->GetHeroAttributeComponent()->AddTag(TEXT("Character.State.NotMoveable"));
        GreystoneCharacter->GetHeroAttributeComponent()->AddTag(TEXT("Character.State.NotAttackable"));
    }
}