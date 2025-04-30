// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Aurora/AuroraSpawnCatalystNotify.h"
#include "Actors/AuroraFrostCatalyst.h"
#include "Player/YggHeroAurora.h"

void UAuroraSpawnCatalystNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!IsValid(MeshComp) || !IsValid(MeshComp->GetOwner())) return;

    AYggHeroAurora* Aurora = Cast<AYggHeroAurora>(MeshComp->GetOwner());
    if (!Aurora) return;

    if (Aurora->HasAuthority())
    {
        if (Aurora->PendingCatalyst != nullptr) return;

        const FTransform SpawnTM = MeshComp->GetSocketTransform(TEXT("Muzzle_02"), RTS_World);

        FActorSpawnParameters Params;
        Params.Owner = Aurora;
        Params.Instigator = Cast<APawn>(Aurora);
        Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

        AAuroraFrostCatalyst* Catalyst = GetWorld()->SpawnActor<AAuroraFrostCatalyst>(
            BPCatalyst,
            SpawnTM.GetLocation(),
            SpawnTM.GetRotation().Rotator(),
            Params
        );

        if (!Catalyst) return;
        
        Catalyst->AttachToComponent(MeshComp, FAttachmentTransformRules::SnapToTargetNotIncludingScale, TEXT("Muzzle_02"));

        Aurora->PendingCatalyst = Catalyst;
    }
    else
    {
        // 클라이언트는 서버에 단 한 번만 RPC 호출
        if (Aurora->PendingCatalyst == nullptr)
        {
            Aurora->Server_SpawnCatalyst();
        }
    }
}