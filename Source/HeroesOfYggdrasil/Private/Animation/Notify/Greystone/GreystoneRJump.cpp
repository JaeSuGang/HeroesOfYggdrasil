// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Greystone/GreystoneRJump.h"
#include "Interfaces/YggHeroInterface.h"
#include "Player/YggHeroGreystone.h"
#include "Attribute/HeroAttributeComponent.h"
#include "Animation/YggHeroAniminstance.h"

#include "MainGame/UI/MainGameHUD.h"
#include "MainGame/UI/YggMainGameUserWidget.h"
#include "MainGame/UI/YggCastingBarUserWidget.h"

void UGreystoneRJump::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp || !MeshComp->GetOwner()) return;

    AYggHeroGreystone* Greystone = Cast<AYggHeroGreystone>(MeshComp->GetOwner());
    if (!IsValid(Greystone)) return;

    APlayerController* PlayerController = MeshComp->GetOwner()->GetWorld()->GetFirstPlayerController();
    AMainGameHUD* MainGameHUD = Cast<AMainGameHUD>(PlayerController->GetHUD());
    if (!MainGameHUD)
        return;

    UYggMainGameUserWidget* MainGameWidget = MainGameHUD->GetMainGameWidget();
    if (!MainGameWidget)
        return;

    UYggCastingBarUserWidget* CastingBarUserWidget = MainGameWidget->GetCastingBarWidget();
    if (!CastingBarUserWidget)
        return;

    CastingBarUserWidget->StartCasting(Greystone->GetHeroAttributeComponent()->SkillRMaxContinueTime);

    if (auto* AnimInstance = MeshComp->GetAnimInstance())
    {
        UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();

        if (CurrentMontage)
        {
            AnimInstance->Montage_Pause(CurrentMontage);

            float ContinueTime = Greystone->GetHeroAttributeComponent()->SkillRMaxContinueTime;

            MeshComp->GetWorld()->GetTimerManager().SetTimer(JumpTimerHandle, [AnimInstance, CurrentMontage]()
            {
                AnimInstance->Montage_Resume(CurrentMontage);
            }, ContinueTime, false);
        }
    }
   
    if (Greystone->GetClass()->ImplementsInterface(UYggHeroInterface::StaticClass()))
    {
        Greystone->GetHeroAttributeComponent()->RemoveTag(TEXT("Character.State.NotMoveable"));
        Greystone->GetHeroAttributeComponent()->RemoveTag(TEXT("Character.State.NotAttackable"));
    }    
}