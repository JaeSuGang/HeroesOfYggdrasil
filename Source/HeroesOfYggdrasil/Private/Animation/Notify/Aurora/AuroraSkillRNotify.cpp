// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Aurora/AuroraSkillRNotify.h"
#include "Player/YggHeroAurora.h"
#include "Enemy/EnemyCharacter.h"
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"
#include "Attribute/HeroAttributeComponent.h"

void UAuroraSkillRNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!IsValid(MeshComp) || !IsValid(MeshComp->GetOwner())) return;

	AYggHeroAurora* Aurora = Cast<AYggHeroAurora>(MeshComp->GetOwner());
	if (!IsValid(Aurora)) return;

    if (!Aurora->HasAuthority())
        return;

    UYggAttackCapsuleComponent* SkillRComponent = Aurora->SkillRAttackCapsuleComponent;
    if (!SkillRComponent) return;

    TArray<AActor*> OverlappingEnemies;
    SkillRComponent->GetOverlappingActors(OverlappingEnemies, AEnemyCharacter::StaticClass());

    for (AActor* EnemyActor : OverlappingEnemies)
    {
        AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(EnemyActor);
        if (Enemy)
        {
            Enemy->ApplyStun();

            float ContinueTime = Aurora->GetHeroAttributeComponent()->SkillQMaxContinueTime;

            MeshComp->GetWorld()->GetTimerManager().SetTimer(FreezeTimerHandle, [Enemy]()
            {
                Enemy->ClearStun();
            }, ContinueTime, false);
        }
    }
}