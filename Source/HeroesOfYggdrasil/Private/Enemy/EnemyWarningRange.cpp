// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/EnemyWarningRange.h"

#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

#include "Component/SceneComponent/YggAttackCapsuleComponent.h"

#include "Player/YggHero.h"
#include "Enemy/EnemyCharacter.h"

// Sets default values
AEnemyWarningRange::AEnemyWarningRange()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

    PrimaryActorTick.bCanEverTick = true;

    PlaneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlaneMesh"));
    RootComponent = PlaneMesh;

    {
        BugTickCollision = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("BugCollision"));
        BugTickCollision->SetupAttachment(PlaneMesh);
        BugTickCollision->CollisionOff();
        BugTickCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyWarningRange::OverLap);
    }
}

// Called when the game starts or when spawned
void AEnemyWarningRange::BeginPlay()
{
	Super::BeginPlay();

    if (WarningMaterial != nullptr && AOEDataTable != nullptr)
    {
        FWarningAreaDataRow* Row = AOEDataTable->FindRow<FWarningAreaDataRow>(FName("BugBall"), nullptr);

        if (Row)
        {
            if (Row->PlaneMesh)
            {
                PlaneMesh->SetStaticMesh(Row->PlaneMesh);
            }

            if (Row->WarningMaterial)
            {
                DynamicMaterial = UMaterialInstanceDynamic::Create(Row->WarningMaterial, this);
                PlaneMesh->SetMaterial(0, DynamicMaterial);
            }

            Duration = Row->Duration;
            TimeElapsed = Row->TimeElapsed;
        }
    }
 
    if (DynamicMaterial != nullptr)
    {
        float Alpha = 0.2f;
        DynamicMaterial->SetScalarParameterValue("WarningAlpha", Alpha);
    }
    SetActorScale3D(FVector(2.0f, 2.0f, 1.0f));
}

// Called every frame
void AEnemyWarningRange::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TimeElapsed += DeltaTime;

    ChangeArea();

    if (TimeElapsed > Duration)
    {
        SpawnBugEffect();
        BugTickCollision->SetCapsuleSize(200.0f, 100.0f);
        BugTickCollision->CollisionOn();
        Destroy();
        return;
    }

    DrawDebugCapsule(
        GetWorld(),
        BugTickCollision->GetComponentLocation(),
        BugTickCollision->GetUnscaledCapsuleHalfHeight(),
        BugTickCollision->GetUnscaledCapsuleRadius(),
        BugTickCollision->GetComponentQuat(),
        FColor::Red,
        false,          // 지속 시간
        -1.0f,
        0,
        2.0f            // 선 두께
    );

}

void AEnemyWarningRange::ChangeArea()
{
    float Progress = FMath::Clamp(TimeElapsed / Duration, 0.0f, 1.0f);
    
    FVector TargetScale(2.0f, 2.0f, 1.0f);
 
    SetActorScale3D(TargetScale * Progress);
}

void AEnemyWarningRange::SpawnBugEffect()
{
    if (IsValid(BugBallParticle))
    {
        UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            BugBallParticle,
            GetActorLocation(),
            GetActorRotation(),
            FVector(10.0f),
            true  // 자동 파괴
        );
    }
}

void AEnemyWarningRange::HideAllComponents()
{
    TArray<UActorComponent*> Components;
    GetComponents(Components);

    for (UActorComponent* Comp : Components)
    {
        if (UPrimitiveComponent* Prim = Cast<UPrimitiveComponent>(Comp))
        {
            Prim->SetVisibility(false, true);  // bPropagateToChildren = true
            //Prim->SetHiddenInGame(true);       // 게임에서도 숨김 처리
        }
    }
}

void AEnemyWarningRange::OverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (IsValid(OtherActor))
    {
        AYggHero* Hero = Cast<AYggHero>(OtherActor);

        if (IsValid(Hero))
        {
            if (Hero && Hero->GetMesh() && BugTickCollision)
            {
                FVector Center = Hero->GetMesh()->Bounds.Origin;

               /* BugTickCollision->SetWorldLocation(Center);

                BugTickCollision->AttachToComponent(
                    Hero->GetMesh(),
                    FAttachmentTransformRules::KeepWorldTransform
                );
                BugTickCollision->SetSimulatePhysics(false);*/
            }
        }
    }
}

void AEnemyWarningRange::SetCollisionOwnerEnemy(AEnemyCharacter* _Enemy)
{
    if (IsValid(_Enemy))
    {

        AYggCharacter* YggCharacterEnemy = Cast<AYggCharacter>(_Enemy);
        BugTickCollision->SetOwnerCharacter(YggCharacterEnemy);
    }
}
