// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/YggDeathNotify.h"

void UYggDeathNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if(!IsValid(MeshComp) || !IsValid(MeshComp->GetOwner())) return;

	if (UAnimInstance* AnimInstance = MeshComp->GetAnimInstance())
	{
		UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();

		if (CurrentMontage)
		{
			AnimInstance->Montage_Pause(CurrentMontage);
		}
	}
}
