// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Greystone/GreystoneRJump.h"
#include "Interfaces/YggHeroInterface.h"
#include "Player/YggHeroGreystone.h"
#include "Attribute/HeroAttributeComponent.h"

void UGreystoneRJump::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp || !MeshComp->GetOwner()) return;

    if (auto* AnimInstance = MeshComp->GetAnimInstance())
    {
        UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();

        if (CurrentMontage)
        {
            AnimInstance->Montage_Pause(CurrentMontage);

            FTimerHandle TimerHandle;
            MeshComp->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [AnimInstance, CurrentMontage]()
            {
                AnimInstance->Montage_Resume(CurrentMontage);
            }, 2.0f, false);
        }
    }

    AYggHeroGreystone* GreystoneCharacter = Cast<AYggHeroGreystone>(MeshComp->GetOwner());
    if (GreystoneCharacter && GreystoneCharacter->GetClass()->ImplementsInterface(UYggHeroInterface::StaticClass()))
    {
        GreystoneCharacter->GetHeroAttributeComponent()->RemoveTag(TEXT("Character.State.NotMoveable"));
        GreystoneCharacter->GetHeroAttributeComponent()->RemoveTag(TEXT("Character.State.NotAttackable"));
    }    
}