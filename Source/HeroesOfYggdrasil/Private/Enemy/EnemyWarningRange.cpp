// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/EnemyWarningRange.h"

#include "Particles/ParticleSystem.h"
#include "Kismet/GameplayStatics.h"

#include "Component/SceneComponent/YggAttackCapsuleComponent.h"

#include "Player/YggHero.h"
#include "Enemy/EnemyCharacter.h"
#include "Global/YggTickActor.h"

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
    FWarningAreaDataRow* Row = AOEDataTable->FindRow<FWarningAreaDataRow>(FName("BugBall"), nullptr);

    if (WarningMaterial != nullptr && AOEDataTable != nullptr)
    {
        if (Row != nullptr)
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

    SetActorScale3D(Row->ScaleVector);
}

// Called every frame
void AEnemyWarningRange::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    TimeElapsed += DeltaTime;

    ChangeArea();

    if (TimeElapsed > Duration)
    {
        SpawnEffect();
        BugTickCollision->SetCapsuleSize(100.0f, 100.0f);
        BugTickCollision->CollisionOn();
        Destroy();
        return;
    }
}

void AEnemyWarningRange::ChangeArea()
{
    FWarningAreaDataRow* Row = AOEDataTable->FindRow<FWarningAreaDataRow>(FName("BugBall"), nullptr);
    
    if (Row != nullptr)
    {
        float Progress = FMath::Clamp(TimeElapsed / Duration, 0.0f, 1.0f);

        FVector TargetScale = Row->ScaleVector;

        SetActorScale3D(TargetScale * Progress);
    }
    
}

void AEnemyWarningRange::SpawnEffect()
{
    FWarningAreaDataRow* Row = AOEDataTable->FindRow<FWarningAreaDataRow>(FName("BugBall"), nullptr);

    if (Row == nullptr)
    {
        return;
    }

    if (IsValid(BugBallParticle))
    {
        UGameplayStatics::SpawnEmitterAtLocation(
            GetWorld(),
            BugBallParticle,
            GetActorLocation(),
            GetActorRotation(),
            FVector(Row->EffectScaleFloat),
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
            Prim->SetVisibility(false, true);  
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
            if (Hero)
            {
                if (IsValid(YggCharacterEnemy))
                {
                    YggCharacterEnemy->OnHeroEnteredRange.Broadcast(Hero);
                }
                
            }
        }
    }
}

void AEnemyWarningRange::SetCollisionOwnerEnemy(AEnemyCharacter* _Enemy)
{
    if (IsValid(_Enemy))
    {

        YggCharacterEnemy = _Enemy;
        BugTickCollision->SetOwnerCharacter(YggCharacterEnemy);
    }
}
