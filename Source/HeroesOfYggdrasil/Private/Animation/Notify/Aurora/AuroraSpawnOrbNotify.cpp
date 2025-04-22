// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Aurora/AuroraSpawnOrbNotify.h"
#include "Actors/AuroraOrb.h"
#include "Player/YggHero.h"
#include "Attribute/HeroAttributeComponent.h"

void UAuroraSpawnOrbNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!IsValid(MeshComp) || !IsValid(MeshComp->GetOwner())) return;

    if (!OrbClass) return;

    FVector SpawnLoc = MeshComp->GetBoneLocation(TEXT("upperarm_r"));
    FRotator SpawnRot = MeshComp->GetComponentRotation();

    FActorSpawnParameters Params;
    Params.Owner = MeshComp->GetOwner();
    Params.Instigator = MeshComp->GetOwner()->GetInstigator();

    AYggHero* Hero = Cast<AYggHero>(MeshComp->GetOwner());
    if (!IsValid(Hero)) return;
    float AttPower = Hero->GetHeroAttributeComponent()->AttackInfo.SkillCoefficient * Hero->GetHeroAttributeComponent()->AttackPoints;

    AAuroraOrb* Orb = GetWorld()->SpawnActor<AAuroraOrb>(OrbClass, SpawnLoc, SpawnRot, Params);
    if (!IsValid(Orb)) return;
    Orb->SetAttPower(AttPower);
}
