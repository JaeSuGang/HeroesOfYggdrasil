// Coded By AssortRock Unreal Engine Class Project


#include "Actors/AuroraFrostMeteor.h"

#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"

#include "Particles/Emitter.h"
#include "Particles/ParticleEmitter.h"
#include "Particles/ParticleSystem.h"
#include "Particles/ParticleSystemComponent.h"
#include "Particles/ParticleLODLevel.h"
#include "Particles/ParticleModuleRequired.h"

#include "Attribute/HeroAttributeComponent.h"
#include "Enemy/EnemyCharacter.h"
#include "Player/YggHeroAurora.h"

// Sets default values
AAuroraFrostMeteor::AAuroraFrostMeteor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootScene = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));
    SetRootComponent(RootScene);

    MeteorCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("OrbCapsule"));
    MeteorCapsule->SetupAttachment(RootScene);

    MeteorCapsule->InitCapsuleSize(600.0f, 600.0f);
    MeteorCapsule->SetCapsuleHalfHeight(800.0f);
    MeteorCapsule->AddRelativeRotation(FRotator(0.0f, 0.0f, 0.0f));
    MeteorCapsule->SetRelativeLocation(FVector(0.0f, 0.0f, -500.0f));

    MeteorCapsule->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);

    MeteorCapsule->OnComponentBeginOverlap.AddDynamic(this, &AAuroraFrostMeteor::OnMeteorOverlapBegin);
    MeteorCapsule->OnComponentEndOverlap.AddDynamic(this, &AAuroraFrostMeteor::OnMeteorOverlapEnd);
}

// Called when the game starts or when spawned
void AAuroraFrostMeteor::BeginPlay()
{
	Super::BeginPlay();
    CachedOwner = Cast<AYggHeroAurora>(GetOwner());

    // 0. 높이 고정 이동
    FVector NewLocation = GetActorLocation();
    NewLocation.Z = 1000.f;
    SetActorLocation(NewLocation);

    // 1. MeteorPortal 스폰
    if (MeteorPortal)
    {
        UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            MeteorPortal,
            GetActorTransform(),
            true
        );
    }

    // 2. 0.5초 후 MeteorShower 스폰 예약
    GetWorldTimerManager().SetTimer(
        MeteorTimerHandle,
        this,
        &AAuroraFrostMeteor::SpawnMeteorShower,
        0.5f,
        false
    );

    // 3. 데미지 설정
    if (AYggHeroAurora* Aurora = Cast<AYggHeroAurora>(GetOwner()))
    {
        Coefficient = Aurora->GetHeroAttributeComponent()->SkillEInfo.SkillCoefficient;
    }
    
    // 4. 이미 Collision 하고 있는 몬스터 처리.
    TArray<AActor*> OverlappedActors;
    MeteorCapsule->GetOverlappingActors(OverlappedActors, AEnemyCharacter::StaticClass());

    for (AActor* Actor : OverlappedActors)
    {
        if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(Actor))
        {
            AYggHeroAurora* Aurora = Cast<AYggHeroAurora>(GetOwner());
            if (!Aurora) return;

            AttPower = DamageLogic(Aurora->GetAttributeComponent(), Enemy->GetAttributeComponent());
            
            Enemy->GetAttributeComponent()->Server_TakeDamage(AttPower);
        }
    }

   /* DrawDebugCapsule(
        GetWorld(),
        MeteorCapsule->GetComponentLocation(),
        MeteorCapsule->GetScaledCapsuleHalfHeight(),
        MeteorCapsule->GetScaledCapsuleRadius(),
        MeteorCapsule->GetComponentQuat(),
        FColor::Green,
        true
    );*/
}

// Called every frame
void AAuroraFrostMeteor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAuroraFrostMeteor::OnMeteorOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!IsValid(OtherActor) || OtherActor == this || !IsValid(OtherComp)) return;
    
    if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
    {
        if (IsValid(Enemy))
        {
            FTimerHandle TimerHandle;
            GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, WeakEnemy = TWeakObjectPtr<AEnemyCharacter>(Enemy)]()
                {
                    if (IsValid(this) && WeakEnemy.IsValid())
                    {
                        ApplyPeriodicDamage(WeakEnemy.Get());
                    }
                },
                0.5f, true);
            EnemyDamageTimers.Add(Enemy, TimerHandle);
        }
    }
}

void AAuroraFrostMeteor::OnMeteorOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
    {
        if (FTimerHandle* Handle = EnemyDamageTimers.Find(Enemy))
        {
            GetWorld()->GetTimerManager().ClearTimer(*Handle);
            EnemyDamageTimers.Remove(Enemy);
        }
    }
}

void AAuroraFrostMeteor::SpawnMeteorShower()
{
    if (MeteorShower)
    {
        UParticleSystemComponent* ParticleComp = UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            MeteorShower,
            GetActorTransform(),
            true
        );

        // 지우기 타이머 설정.
        if (ParticleComp && ParticleComp->Template)
        {
            float MaxDuration = 0.f;
            bool bHasInfinite = false;

            for (const FParticleEmitterInstance* EmitterInst : ParticleComp->EmitterInstances)
            {
                if (EmitterInst && EmitterInst->SpriteTemplate)
                {
                    UParticleLODLevel* LODLevel = EmitterInst->SpriteTemplate->GetLODLevel(0);
                    if (LODLevel && LODLevel->RequiredModule)
                    {
                        const float EmitterDuration = LODLevel->RequiredModule->EmitterDuration;

                        const int32 EmitterLoops = LODLevel->RequiredModule->EmitterLoops;

                        if (EmitterLoops == 0 || EmitterDuration <= 0)
                        {
                            bHasInfinite = true;
                            break;
                        }

                        MaxDuration = FMath::Max(MaxDuration, EmitterDuration);
                    }
                }
            }

            // 루프가 있는 경우 3초 뒤 파괴
            if (bHasInfinite)
            {
                MaxDuration = 3.f;
            }

            GetWorld()->GetTimerManager().SetTimer(
                DestroyTimerHandle,
                this,
                &AAuroraFrostMeteor::DestroyMeteor,
                MaxDuration,
                false
            );
        }
    }
}

void AAuroraFrostMeteor::DestroyMeteor()
{
    for (auto& Elem : EnemyDamageTimers)
    {
        GetWorld()->GetTimerManager().ClearTimer(Elem.Value);
    }
    EnemyDamageTimers.Empty();

    Destroy();
}

float AAuroraFrostMeteor::DamageLogic(UCharacterAttributeComponent* Attack, UCharacterAttributeComponent* Hit)
{
    UCharacterAttributeComponent* AttackAttributeComponent = Attack;
    UCharacterAttributeComponent* HitAttributeComponent = Hit;
    float Damage;
    // 공격력 계산
    Damage = AttackAttributeComponent->AttackPoints * Coefficient;
    // 방어력 계산
    Damage = Damage * (100 / (100 + HitAttributeComponent->DefensePoints));
    // 크리티컬 확률 계산 
    if (FMath::FRand() <= AttackAttributeComponent->CriticalChance)
    {
        Damage = Damage * (1 + AttackAttributeComponent->CriticalDamageRate);
    }
    return Damage;
}

void AAuroraFrostMeteor::ApplyPeriodicDamage(AEnemyCharacter* Enemy)
{
    if (!CachedOwner.IsValid() || !IsValid(Enemy) || !IsValid(this) || !IsValid(GetOwner())) return;

    AYggHeroAurora* Aurora = Cast<AYggHeroAurora>(GetOwner());
    if (!IsValid(Aurora) || !IsValid(Aurora->GetHeroAttributeComponent())) return;
        
    if (IsValid(Enemy->GetAttributeComponent()))
    {
        Enemy->GetAttributeComponent()->Server_TakeDamage(AttPower);
       
        FString TestString = FString::SanitizeFloat(AttPower);

        GEngine->AddOnScreenDebugMessage(-1, 1.0f, FColor::Green, TestString);
    }        
}
