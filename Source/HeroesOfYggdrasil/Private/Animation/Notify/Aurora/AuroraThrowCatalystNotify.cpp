// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Aurora/AuroraThrowCatalystNotify.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Actors/AuroraFrostCatalyst.h"
#include "Player/YggHeroAurora.h"

void UAuroraThrowCatalystNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
    if (!MeshComp || !MeshComp->GetOwner()) return;
    AYggHeroAurora* Aurora = Cast<AYggHeroAurora>(MeshComp->GetOwner());
    if (!Aurora || !Aurora->PendingCatalyst) return;

    if (Aurora->HasAuthority())
    {
        Aurora->Multicast_ThrowCatalyst(Aurora->PendingCatalyst, Aurora->MagicTargetPoint);
    }
    else
    {
        Aurora->Server_ThrowCatalyst();
    }
    /*Aurora->MagicCircleOff();

    AAuroraFrostCatalyst* Catalyst = Aurora->PendingCatalyst;
    Aurora->PendingCatalyst = nullptr;

    Catalyst->DetachFromActor(FDetachmentTransformRules::KeepWorldTransform);

    auto* ProjMove = Catalyst->FindComponentByClass<UProjectileMovementComponent>();
    if (!ProjMove) return;

    FVector Start = Catalyst->GetActorLocation();
    FVector Target = Aurora->MagicTargetPoint;

    FVector LaunchVel;
    bool bHaveVel = UGameplayStatics::SuggestProjectileVelocity_CustomArc(
        this,
        LaunchVel,
        Start,
        Target,
        0.f,
        0.75f
    );

    if (bHaveVel)
    {
        ProjMove->Velocity = LaunchVel * 1.2f;
        ProjMove->Activate(true);
    }
    else
    {
        UE_LOG(LogTemp, Warning, TEXT("Failed to calculate projectile velocity!"));
    }*/
}