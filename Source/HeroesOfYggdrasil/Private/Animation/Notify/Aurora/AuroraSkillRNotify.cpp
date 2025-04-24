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

            if (FTimerHandle* ExistingHandle = ActiveStunTimers.Find(Enemy))
            {
                GetWorld()->GetTimerManager().ClearTimer(*ExistingHandle);
                ActiveStunTimers.Remove(Enemy);
            }

            float ContinueTime = Aurora->GetHeroAttributeComponent()->SkillRMaxContinueTime;

            FTimerHandle NewHandle;
            FTimerDelegate Delegate;
            Delegate.BindWeakLambda(this, [Enemy]()
            {
                if (Enemy && Enemy->IsValidLowLevel())
                {
                    Enemy->ClearStun();
                }
            });

            GetWorld()->GetTimerManager().SetTimer(NewHandle, Delegate, ContinueTime, false);
            ActiveStunTimers.Add(Enemy, NewHandle);
        }
    }
}