// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/AnimNotifySaveAttack.h"
#include "Player/YggHeroKhaimera.h"


void UAnimNotifySaveAttack::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (MeshComp && MeshComp->GetOwner())
    {
        AYggHeroKhaimera* Hero = Cast<AYggHeroKhaimera>(MeshComp->GetOwner());

        if (Hero)
        {
     
            Hero->SaveAttack();
        }
    }
}
