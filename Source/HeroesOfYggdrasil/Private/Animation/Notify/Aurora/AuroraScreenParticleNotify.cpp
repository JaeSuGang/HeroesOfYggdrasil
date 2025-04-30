// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Aurora/AuroraScreenParticleNotify.h"
#include "Kismet/GameplayStatics.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PlayerController.h"
#include "Particles/ParticleSystemComponent.h"

void UAuroraScreenParticleNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!ParticleTemplate || !MeshComp) return;
    
    UWorld* World = MeshComp->GetWorld();
    if (!World) return; 

    APawn* Pawn = Cast<APawn>(MeshComp->GetOwner());
    if (!Pawn) return;    

    if (!Pawn->IsLocallyControlled()) return;

    UCameraComponent* CameraComp = Pawn->FindComponentByClass<UCameraComponent>();
    UParticleSystemComponent* PSC = nullptr;

    if (CameraComp)
    {
        PSC = UGameplayStatics::SpawnEmitterAttached(
            ParticleTemplate,
            CameraComp,
            NAME_None,
            LocationOffset,
            FRotator::ZeroRotator,
            EAttachLocation::KeepRelativeOffset,
            true
        );
    }
    else
    {
        FVector SpawnLocation;
        FRotator SpawnRotation;
        Pawn->GetActorEyesViewPoint(SpawnLocation, SpawnRotation);
        SpawnLocation += LocationOffset;

        PSC = UGameplayStatics::SpawnEmitterAtLocation(
            World,
            ParticleTemplate,
            SpawnLocation,
            SpawnRotation,
            true
        );
    }
}
