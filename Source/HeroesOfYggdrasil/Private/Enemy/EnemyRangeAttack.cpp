// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/EnemyRangeAttack.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/DataTable.h"
#include "Components/SphereComponent.h"

// Sets default values
AEnemyRangeAttack::AEnemyRangeAttack()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    DefualtSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefualtSceneRoot"));

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("EnemyProjectileMovement"));

    PoisonMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));
    PoisonMesh->SetupAttachment(DefualtSceneRoot);

    PoisonCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionMesh"));
    PoisonCollision->SetupAttachment(DefualtSceneRoot);
    PoisonCollision->SetCollisionProfileName(TEXT("MonsterAttack"));
}

// Called when the game starts or when spawned
void AEnemyRangeAttack::BeginPlay()
{
	Super::BeginPlay();

    FProjectileDataRow* ProjectileDataRow = EnemyProjectileData->FindRow<FProjectileDataRow>(FName("Poison"), nullptr);

    ProjectileMovement->InitialSpeed = ProjectileDataRow->ProjectileData.InitialSpeed;
    ProjectileMovement->MaxSpeed = ProjectileDataRow->ProjectileData.MaxSpeed;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;
    ProjectileMovement->Activate();

    if (ProjectileDataRow != nullptr)
    {
        UStaticMesh* StaticMesh = ProjectileDataRow->StaticMesh.LoadSynchronous();
        if (StaticMesh != nullptr)
        {
            PoisonMesh->SetStaticMesh(StaticMesh);
            PoisonMesh->SetMobility(EComponentMobility::Movable);
            PoisonMesh->SetSimulatePhysics(false);
        }
    }

    PoisonCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyRangeAttack::OverLap);

    DestroyTime = 3.0f;
}

// Called every frame
void AEnemyRangeAttack::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    DestroyTime -= DeltaTime;
    if (DestroyTime <= 0.0f)
    {
        this->Destroy();
    }
}

void AEnemyRangeAttack::OverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (IsValid(OtherActor))
    {
        AYggHero* Hero = Cast<AYggHero>(OtherActor);

        if (Hero != nullptr)
        {
            //AActor* Ptr = GetWorld()->SpawnActor<AActor>(APostion::Staticclass());

            // PoisonMesh->AttachToComponent(Hero->GetMesh(), FAttachmentTransformRules::KeepWorldTransform);

            //Ptr->AttachToComponent(Hero->GetMesh(), FAttachmentTransformRules::KeepWorldTransform);
            //Ptr->SetSimulatePhysics(false);
            // Ptr->DestroyComponent();
            //ProjectileMovement->StopMovementImmediately();
            //Ptr->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            // Ptr->Deactivate();

            //Destroy();
        }
    }
}

