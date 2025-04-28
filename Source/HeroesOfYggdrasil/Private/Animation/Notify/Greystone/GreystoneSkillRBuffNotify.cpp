// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Greystone/GreystoneSkillRBuffNotify.h"
#include "Player/YggHero.h"
#include "Player/YggHeroGreystone.h"
#include "Attribute/HeroAttributeComponent.h"
#include "Component/SceneComponent/YggCapsuleComponent.h"

void UGreystoneSkillRBuffNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!IsValid(MeshComp) || !IsValid(MeshComp->GetOwner())) return;

	AYggHeroGreystone* Greystone = Cast<AYggHeroGreystone>(MeshComp->GetOwner());
	if (!IsValid(Greystone)) return;

	UYggCapsuleComponent* Capsule = Greystone->GetSkillRBuffCapsule();
    if (!IsValid(Capsule)) return;

    TArray<AActor*> OverlappingActors;
    Capsule->GetOverlappingActors(OverlappingActors, AYggHero::StaticClass());

    for (AActor* Actor : OverlappingActors)
    {
        AYggHero* OverlappedHero = Cast<AYggHero>(Actor);
        if (IsValid(OverlappedHero))
        {
            float Heal = Greystone->GetHeroAttributeComponent()->SkillRInfo.SkillCoefficient * -10.0f;

            OverlappedHero->GetHeroAttributeComponent()->Server_TakeDamage(Heal);
        }
    }
}