// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Aurora/AuroraLevelStartNotify.h"

void UAuroraLevelStartNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(!IsValid(MeshComp) || !IsValid(MeshComp->GetOwner())) return;

    UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
    if (!IsValid(AnimInstance)) return;

    UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();
    if (CurrentMontage)
    {
        AnimInstance->Montage_JumpToSection(FName("Start"), CurrentMontage);
    }
}
