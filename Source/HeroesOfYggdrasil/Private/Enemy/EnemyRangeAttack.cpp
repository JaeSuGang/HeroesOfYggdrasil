// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/EnemyRangeAttack.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/DataTable.h"
#include "Components/SphereComponent.h"
#include "Enemy/EnemyCharacter.h"

// Sets default values
AEnemyRangeAttack::AEnemyRangeAttack()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
    
    {
        bReplicates = true;
        SetReplicateMovement(true);
    }

    DefualtSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefualtSceneRoot"));

    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("EnemyProjectileMovement"));

    ObjectMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ObjectMesh"));
    ObjectMesh->SetupAttachment(DefualtSceneRoot);

    SphereObjectCollision = CreateDefaultSubobject<USphereComponent>(TEXT("CollisionMesh"));
    SphereObjectCollision->SetupAttachment(DefualtSceneRoot);
    SphereObjectCollision->SetCollisionProfileName(TEXT("MonsterAttackCollision"));

    SphereObjectCollision->OnComponentBeginOverlap.AddDynamic(this, &AEnemyRangeAttack::OverLap);
    SphereObjectCollision->OnComponentHit.AddDynamic(this, &AEnemyRangeAttack::OnHit);
}

// Called when the game starts or when spawned
void AEnemyRangeAttack::BeginPlay()
{
	Super::BeginPlay();


    DestroyTime = 3.0f;

    InitializeRangeAttack();
}

void AEnemyRangeAttack::InitializeRangeAttack()
{
    AEnemyCharacter* EnemyCharacter = Cast<AEnemyCharacter>(GetOwner());
    
    if (!IsValid(EnemyCharacter))
    {
        return;
    }

    FString DataKeyString = EnemyCharacter->GetDataKey();
    FName DataName = GetMeshNameByKey(DataKeyString);

    FProjectileDataRow* ProjectileDataRow = EnemyProjectileData->FindRow<FProjectileDataRow>(DataName, nullptr);

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
            ObjectMesh->SetStaticMesh(StaticMesh);
            ObjectMesh->SetMobility(EComponentMobility::Movable);
            ObjectMesh->SetSimulatePhysics(false);
        }
    }
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
    ObjectMesh->SetVisibility(false);
}

void AEnemyRangeAttack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
    ObjectMesh->SetVisibility(false);
}


FName AEnemyRangeAttack::GetMeshNameByKey(const FString& _DataString)
{
    static const TMap<FString, FName> SectionMap = {
        {TEXT("Minion_Witch_0"), FName("BugBall")},
        {TEXT("Minion_Witch_1"), FName("SnowBall")},
        {TEXT("Minion_Witch_2"), FName("LightningBall")},
        {TEXT("Minion_Witch_3"), FName("FireBall")}
    };

    if (const FName* Found = SectionMap.Find(_DataString))
    {
        return *Found;
    }

    return FName("BugBall");
}