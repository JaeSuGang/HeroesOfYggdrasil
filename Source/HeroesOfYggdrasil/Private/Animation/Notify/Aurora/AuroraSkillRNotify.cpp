// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Aurora/AuroraSkillRNotify.h"
#include "Player/YggHeroAurora.h"
#include "Enemy/EnemyCharacter.h"
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"
#include "Attribute/HeroAttributeComponent.h"
#include "Kismet/GameplayStatics.h"

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
            // Freeze 적용.
            Enemy->ApplyStun();

            TWeakObjectPtr<AEnemyCharacter> WeakEnemy = Enemy;

            if (FTimerHandle* ExistingHandle = ActiveStunTimers.Find(WeakEnemy))
            {
                GetWorld()->GetTimerManager().ClearTimer(*ExistingHandle);
                ActiveStunTimers.Remove(WeakEnemy);
            }

            // Freeze 파티클 추가.
            if (PSTemplate)
            {
                UParticleSystemComponent* PSComp = UGameplayStatics::SpawnEmitterAttached(
                    PSTemplate,
                    Enemy->GetMesh(),
                    NAME_None,
                    FVector::ZeroVector,
                    FRotator::ZeroRotator,
                    EAttachLocation::SnapToTarget,
                    true,
                    EPSCPoolMethod::AutoRelease
                );
            }


            // Freeze 해제.
            float ContinueTime = Aurora->GetHeroAttributeComponent()->SkillRMaxContinueTime;

            FTimerHandle NewHandle;
            FTimerDelegate Delegate;
            Delegate.BindWeakLambda(this, [WeakEnemy]()
            {
                if (WeakEnemy.IsValid())
                {
                    WeakEnemy->ClearStun();
                }
            });

            GetWorld()->GetTimerManager().SetTimer(NewHandle, Delegate, ContinueTime, false);
            ActiveStunTimers.Add(WeakEnemy, NewHandle);
        }
    }
}