// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Hero/HeroSkillCastingNotify.h"
#include "Player/YggHero.h"
#include "Attribute/HeroAttributeComponent.h"

void UHeroSkillCastingNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp || !MeshComp->GetOwner()) return;

    AYggHero* Hero = Cast<AYggHero>(MeshComp->GetOwner());
    if (!IsValid(Hero)) return;

    if (SkillQ)
    {
        SkillCastingTime = Hero->GetHeroAttributeComponent()->SkillQMaxCastingTime;
    }
    else if (SkillE)
    {
        SkillCastingTime = Hero->GetHeroAttributeComponent()->SkillEMaxCastingTime;
    }
    else if (SkillR)
    {
        SkillCastingTime = Hero->GetHeroAttributeComponent()->SkillRMaxCastingTime;
    }
    else {
        return;
    }

    Hero->OnSkillCast.Broadcast(SkillCastingTime);

    if (auto* AnimInstance = MeshComp->GetAnimInstance())
    {
        UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();

        if (CurrentMontage)
        {
            AnimInstance->Montage_Pause(CurrentMontage);
                       
            MeshComp->GetWorld()->GetTimerManager().SetTimer(CastingTimerHandle, [AnimInstance, CurrentMontage]()
            {
                AnimInstance->Montage_Resume(CurrentMontage);
            }, SkillCastingTime, false);
        }
    }
}

void UHeroSkillCastingNotify::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropName = PropertyChangedEvent.GetPropertyName();

	if (PropName == GET_MEMBER_NAME_CHECKED(UHeroSkillCastingNotify, SkillQ) && SkillQ)
	{
		SkillE = false;
		SkillR = false;
	}
	else if (PropName == GET_MEMBER_NAME_CHECKED(UHeroSkillCastingNotify, SkillE) && SkillE)
	{
		SkillQ = false;
		SkillR = false;
	}
	else if (PropName == GET_MEMBER_NAME_CHECKED(UHeroSkillCastingNotify, SkillR) && SkillR)
	{
		SkillQ = false;
		SkillE = false;
	}
}