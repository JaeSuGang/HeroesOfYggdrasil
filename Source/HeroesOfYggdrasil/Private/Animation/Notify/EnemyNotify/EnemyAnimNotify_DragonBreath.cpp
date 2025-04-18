// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/EnemyNotify/EnemyAnimNotify_DragonBreath.h"

void UEnemyAnimNotify_DragonBreath::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp) return;

	AActor* Owner = MeshComp->GetOwner();
	if (!Owner) return;

	UAnimInstance* AnimInstance = MeshComp->GetAnimInstance();
	if (!AnimInstance) return;

	UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();
	if (CurrentMontage)
	{
		AnimInstance->Montage_SetPlayRate(CurrentMontage, 0.4f);
	}
}
