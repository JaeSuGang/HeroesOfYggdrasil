// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/YggDeathNotify.h"
#include "Player/YggHero.h"

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
		
	AYggHero* Hero = Cast<AYggHero>(MeshComp->GetOwner());
	if (Hero)
	{
		float RespawnTime = Hero->RespawnTime + Hero->GetDeathCount() * 5.0f;
		
		MeshComp->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [Hero]()
		{
			Hero->Respawn();
		}, RespawnTime, false);
	}
}
