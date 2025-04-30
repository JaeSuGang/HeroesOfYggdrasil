// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/EnemyProjectile.h"

#include "Engine/DataTable.h"

#include "GameFramework/ProjectileMovementComponent.h"

#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"

#include "NPC/Yggdrasil.h"
#include "Enemy/EnemyCharacter.h"

// Sets default values
AEnemyProjectile::AEnemyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    
    {
        bReplicates = true;
        SetReplicateMovement(true);
    }

    DefualtSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefualtSceneRoot"));
    
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("EnemyProjectileMovement"));
    
    ArrowMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ArrowMesh"));
    ArrowMesh->SetupAttachment(DefualtSceneRoot);

    {
        ArrowSphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionMesh"));
        ArrowSphereCollision->SetCollisionProfileName(TEXT("MonsterAttackCollision"));
        ArrowSphereCollision->SetupAttachment(DefualtSceneRoot);
        ArrowSphereCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyProjectile::OverLap);
    }
    DestroyTime = 5.0f;
    ArrowAttack = 0.0f;
}

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
    Super::BeginPlay();


    AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetOwner());
    if (!IsValid(EnemyCharacter)) return;
    FString EnemyDataKey = EnemyCharacter->GetDataKey();
    if (!EnemyDataKey.StartsWith("Minion_Archer"))
    {
        return;
    }
    
    FName RowName = GetArrowNameByDataKey(EnemyDataKey);

    FProjectileDataRow* ProjectileDataRow = EnemyProjectileData->FindRow<FProjectileDataRow>(RowName, nullptr);

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
            ArrowMesh->SetStaticMesh(StaticMesh);
            ArrowMesh->SetMobility(EComponentMobility::Movable);
            ArrowMesh->SetSimulatePhysics(false);
        }
    }

}

// Called every frame
void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

    DestroyTime -= DeltaTime;
    if (DestroyTime <= 0.0f)
    {
        this->Destroy();
    }
}

void AEnemyProjectile::OverLap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    if (IsValid(OtherActor))
    {
        AYggHero* Hero = Cast<AYggHero>(OtherActor);
        
        if (IsValid(Hero))
        {

            Hero->GetAttributeComponent()->Server_TakeDamage(ArrowAttack);
            ArrowMesh->AttachToComponent(Hero->GetMesh(), FAttachmentTransformRules::KeepWorldTransform);
            ArrowMesh->SetSimulatePhysics(false);

            ProjectileMovement->StopMovementImmediately();

            ArrowSphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
            ArrowSphereCollision->Deactivate();
        }

        AYggdrasil* Yggdrasil = Cast<AYggdrasil>(OtherActor);
        
        if (IsValid(Yggdrasil))
        {
            TWeakObjectPtr<AYggdrasil> WeakYggdrasil = Yggdrasil;

            FTimerHandle SpawnTimerHandle;

            GetWorld()->GetTimerManager().SetTimer(SpawnTimerHandle, FTimerDelegate::CreateLambda([this, WeakYggdrasil]()
                {
                    if (WeakYggdrasil.IsValid())
                    {
                        WeakYggdrasil->GetAttributeComponent()->Server_TakeDamage(ArrowAttack);
                        ArrowMesh->AttachToComponent(WeakYggdrasil->GetMesh(), FAttachmentTransformRules::KeepWorldTransform);
                        ArrowMesh->SetSimulatePhysics(false);

                        ProjectileMovement->StopMovementImmediately();

                        ArrowSphereCollision->SetCollisionEnabled(ECollisionEnabled::NoCollision);
                        ArrowSphereCollision->Deactivate();
                    }
                }), 0.1f, false);
            
            
        }

    }
}


void AEnemyProjectile::SetAttackFloat(float _Attack)
{
    ArrowAttack = _Attack;
}


FName AEnemyProjectile::GetArrowNameByDataKey(const FString& _Datakey)
{
    static const TMap<FString, FName> ArrowData =
    {
        {TEXT("Minion_Archer_0"), FName("Arrow_0")},
        {TEXT("Minion_Archer_1"), FName("Arrow_1")},
        {TEXT("Minion_Archer_2"), FName("Arrow_2")},
        {TEXT("Minion_Archer_3"), FName("Arrow_2")}
    };


    if (const FName* FindName = ArrowData.Find(_Datakey))
    {
        return *FindName;
    }

    return FName("Arrow_0");
}
