// Coded By AssortRock Unreal Engine Class Project


#include "Actors/AuroraOrb.h"

#include "Components/CapsuleComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/OverlapResult.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/PlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

#include "Enemy/EnemyCharacter.h"
#include "Player/YggHeroAurora.h"
#include "Attribute/HeroAttributeComponent.h"

// Sets default values
AAuroraOrb::AAuroraOrb()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;

    OrbCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("OrbCapsule"));
    SetRootComponent(OrbCapsule);
    OrbCapsule->InitCapsuleSize(20.f, 20.f);
    OrbCapsule->AddRelativeRotation(FRotator(0.0f, 0.0f, 90.0f));

    OrbCapsule->SetCollisionObjectType(ECollisionChannel::ECC_GameTraceChannel3);
    OrbCapsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel5, ECR_Overlap);
    OrbCapsule->SetCollisionResponseToChannel(ECollisionChannel::ECC_GameTraceChannel6, ECR_Overlap);

    OrbCapsule->SetHiddenInGame(true);
    OrbCapsule->SetVisibility(true);

    MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
    MeshComp->SetupAttachment(OrbCapsule);
    MeshComp->SetRelativeLocation(FVector::ZeroVector);
    MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    OrbCapsule->OnComponentBeginOverlap.AddDynamic(this, &AAuroraOrb::OnOrbOverlapBegin);
}

// Called when the game starts or when spawned
void AAuroraOrb::BeginPlay()
{
    Super::BeginPlay();

    APlayerController* PC = GetWorld()->GetFirstPlayerController();
    if (PC && PC->GetPawn())
    {
        // 1. 카메라 위치 & 회전 획득
        FVector CameraLoc;
        FRotator CameraRot;
        PC->GetPlayerViewPoint(CameraLoc, CameraRot);

        // 2. 뷰포트 중앙 좌표 계산
        int32 ViewportSizeX, ViewportSizeY;
        PC->GetViewportSize(ViewportSizeX, ViewportSizeY);
        FVector2D ScreenCenter = FVector2D(ViewportSizeX * 0.5f, ViewportSizeY * 0.5f);

        // 3. 화면 중앙 → 월드 방향 변환
        FVector WorldDirection;
        FVector DummyVector;
        PC->DeprojectScreenPositionToWorld(
            ScreenCenter.X,
            ScreenCenter.Y,
            DummyVector,
            WorldDirection
        );

        // 4. Line Trace 파라미터 설정
        FVector TraceStart = CameraLoc;
        FVector TraceEnd = TraceStart + (WorldDirection * 10000.f);
        FHitResult HitResult;
        FCollisionQueryParams TraceParams;
        TraceParams.AddIgnoredActor(PC->GetPawn());
        TraceParams.AddIgnoredActor(this);

        // 5. Line Trace 수행
        bool bHit = GetWorld()->LineTraceSingleByChannel(
            HitResult,
            TraceStart,
            TraceEnd,
            ECC_Visibility,
            TraceParams
        );

        // 6. 타겟 포인트 결정
        TargetPoint = bHit ? HitResult.Location : TraceStart + (WorldDirection * 10000.f);

        // 7. 이동 방향 계산 (오브 현재 위치 → 타겟 포인트)
        MoveDirection = (TargetPoint - GetActorLocation()).GetSafeNormal();
        
        if (!MoveDirection.IsNearlyZero())
        {
            FRotator NewRotation = FRotationMatrix::MakeFromYZ(
                MoveDirection,
                FVector::UpVector
            ).Rotator();

            SetActorRotation(NewRotation + FRotator(0, 0, 90.f));
        }

        // 디버그
        // DrawDebugLine(GetWorld(), CameraLoc, TargetPoint, FColor::Green, false, 2.f);
        // DrawDebugSphere(GetWorld(), TargetPoint, 30.f, 12, FColor::Red, false, 2.f);
    }

    // 파괴 타이머
    TWeakObjectPtr<AAuroraOrb> WeakThis(this);
    GetWorld()->GetTimerManager().SetTimer(OrbTimer, [WeakThis]() {
        if (WeakThis.IsValid())
        {
            WeakThis->Destroy();
        }
    }, 3.0f, false);
    
    if (PSTrail)
    {
        UGameplayStatics::SpawnEmitterAttached(
            PSTrail,
            OrbCapsule,
            NAME_None,
            FVector::ZeroVector,
            FRotator::ZeroRotator,
            EAttachLocation::KeepRelativeOffset,
            true
        );
    }

    // 호밍 타이머
    GetWorld()->GetTimerManager().SetTimer(HomingTimer, [WeakThis]() {
        if (WeakThis.IsValid())
        {
            WeakThis->bCanHoming = true;
        }
    }, HomingStartDelay, false);
}

void AAuroraOrb::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
    if (UWorld* World = GetWorld())
    {
        World->GetTimerManager().ClearTimer(OrbTimer);
        World->GetTimerManager().ClearTimer(HomingTimer);
    }

    Super::EndPlay(EndPlayReason);
}

// Called every frame
void AAuroraOrb::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    if (!MoveDirection.IsZero())
    {
        FVector NewLoc = GetActorLocation() + MoveDirection * MoveSpeed * DeltaTime;
        SetActorLocation(NewLoc);

        const float DistanceThreshold = 20.f;
        if (FVector::Dist(GetActorLocation(), TargetPoint) < DistanceThreshold)
        {
            if (PSImpact)
            {
                UGameplayStatics::SpawnEmitterAtLocation(
                    GetWorld(),
                    PSImpact,
                    GetActorLocation(),
                    GetActorRotation()
                );
            }

            Destroy();
            return;
        }

        if (bCanHoming)
        {
            if (!TargetEnemy)
            {
                LastHomingDistance = FLT_MAX;
                TArray<FOverlapResult> OverlapResults;
                FCollisionQueryParams CollisionParams;
                CollisionParams.AddIgnoredActor(this);

                FCollisionObjectQueryParams ObjectQueryParams;
                ObjectQueryParams.AddObjectTypesToQuery(EnemyObjectType.GetValue());

                // 주변 적 탐지
                if (GetWorld()->OverlapMultiByObjectType(
                    OverlapResults,
                    GetActorLocation(),
                    FQuat::Identity,
                    ObjectQueryParams,
                    FCollisionShape::MakeSphere(HomingRadius),
                    CollisionParams))
                {
                    float NearestDistance = BIG_NUMBER;

                    // 가장 가까운 적 찾기
                    for (const FOverlapResult& Result : OverlapResults)
                    {
                        if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(Result.GetActor()))
                        {
                            const float Distance = FVector::DistSquared(GetActorLocation(), Enemy->GetActorLocation());
                            if (Distance < NearestDistance)
                            {
                                NearestDistance = Distance;
                                TargetEnemy = Enemy;
                            }
                        }
                    }
                }
            }

            if (TargetEnemy && !IsValid(TargetEnemy))
            {
                TargetEnemy = nullptr;
            }

            // 방향 조정
            if (TargetEnemy)
            {
                /*const FVector TargetLocation = TargetEnemy->GetActorLocation();
                const FVector DesiredDirection = (TargetLocation - GetActorLocation()).GetSafeNormal();

                MoveDirection = FMath::VInterpConstantTo(
                    MoveDirection,
                    DesiredDirection,
                    DeltaTime,
                    HomingStrength
                );

                SetActorRotation(FRotationMatrix::MakeFromYZ(
                    MoveDirection,
                    FVector::UpVector
                ).Rotator() + FRotator(0, 0, 90));*/

                float CurrentDist = FVector::DistSquared(GetActorLocation(), TargetEnemy->GetActorLocation());
                if (CurrentDist > LastHomingDistance)
                {
                    bCanHoming = false;
                }
                else
                {
                    LastHomingDistance = CurrentDist;

                    // 호밍 방향 조정
                    FVector DesiredDir = (TargetEnemy->GetActorLocation() - GetActorLocation()).GetSafeNormal();
                    MoveDirection = FMath::VInterpConstantTo(
                        MoveDirection, DesiredDir, DeltaTime, HomingStrength
                    );
                    SetActorRotation(
                        (FRotationMatrix::MakeFromYZ(MoveDirection, FVector::UpVector).Rotator())
                        + FRotator(0, 0, 90)
                    );
                }
            }
        }
    }
}

void AAuroraOrb::OnOrbOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (!IsValid(OtherActor) || OtherActor == this || !IsValid(OtherComp)) return;
    
    bool bShouldDestroy = false;

    ECollisionChannel Channel = OtherComp->GetCollisionObjectType();
    if (Channel == ECC_GameTraceChannel5 || Channel == ECC_GameTraceChannel6)
    {
        bShouldDestroy = true;
    }
    else if (AEnemyCharacter* Enemy = Cast<AEnemyCharacter>(OtherActor))
    {
        if (IsValid(Enemy))
        {
            AYggHeroAurora* Aurora = Cast<AYggHeroAurora>(GetOwner());
            if (!Aurora) return;

            float Coefficient = Aurora->GetHeroAttributeComponent()->AttackInfo.SkillCoefficient;
            AttPower = DamageLogic(Aurora->GetAttributeComponent(), Enemy->GetAttributeComponent(), Coefficient);

            Enemy->GetAttributeComponent()->Server_TakeDamage(AttPower);
            bShouldDestroy = true;
        }
    }

    if (bShouldDestroy)
    {
        if (PSImpact)
        {
            UGameplayStatics::SpawnEmitterAtLocation(
                GetWorld(),
                PSImpact,
                GetActorLocation(),
                GetActorRotation()
            );
        }

        Destroy();
    }
}

float AAuroraOrb::DamageLogic(UCharacterAttributeComponent* Attack, UCharacterAttributeComponent* Hit, float Coefficient)
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
