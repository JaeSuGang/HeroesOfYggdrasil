// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Aurora/AuroraSpawnOrbNotify.h"
#include "Actors/AuroraOrb.h"

void UAuroraSpawnOrbNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!IsValid(MeshComp) || !IsValid(MeshComp->GetOwner())) return;

    if (!OrbClass) return;

    FVector SpawnLoc = MeshComp->GetSocketLocation(TEXT("Sword_Mid"));
    FRotator SpawnRot = MeshComp->GetComponentRotation();

    FActorSpawnParameters Params;
    Params.Owner = MeshComp->GetOwner();
    Params.Instigator = MeshComp->GetOwner()->GetInstigator();

    GetWorld()->SpawnActor<AAuroraOrb>(OrbClass, SpawnLoc, SpawnRot, Params);
}
