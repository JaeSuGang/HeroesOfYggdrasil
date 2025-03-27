// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Greystone/GreystoneComboNotify.h"
#include "Player/YggHero.h"
#include "Animation/AnimInstance.h"
#include "Animation/YggHeroAnimInstance.h"

void UGreystoneComboNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	AYggHero* Hero = Cast<AYggHero>(MeshComp->GetOwner());
	if (!Hero) return;

	UYggHeroAnimInstance* HeroAnimInstance = Hero->GetHeroAnimInstance();
	if (!HeroAnimInstance) return;

	UAnimMontage* CurrentMontage = HeroAnimInstance->GetCurrentActiveMontage();
	if (!CurrentMontage) return;

	FName CurSection = HeroAnimInstance->Montage_GetCurrentSection();

    FString CurSectionStr = CurSection.ToString();
    FString Prefix = "Attack";
    int32 SectionNumber;

    if (CurSectionStr.RemoveFromStart(Prefix) && CurSectionStr.IsNumeric())
    {
        SectionNumber = FCString::Atoi(*CurSectionStr);
        int32 NextSectionNumber = (SectionNumber + 1) % (MaxCombo + 1);
        FString NextSectionStr = Prefix + FString::FromInt(NextSectionNumber);
        FName NextSection = FName(*NextSectionStr);

        HeroAnimInstance->Montage_JumpToSection(NextSection, CurrentMontage);
    }
}
