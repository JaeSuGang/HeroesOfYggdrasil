// Coded By AssortRock Unreal Engine Class Project


#include "Enemy/EnemyProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Engine/DataTable.h"

// Sets default values
AEnemyProjectile::AEnemyProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("EnemyProjectileMovement"));
   
}

// Called when the game starts or when spawned
void AEnemyProjectile::BeginPlay()
{
    Super::BeginPlay();
    FProjectileDataRow* ProjectileDataRow = EnemyProjectileData->FindRow<FProjectileDataRow>(FName("Arrow"), nullptr);


    ProjectileMovement->InitialSpeed = ProjectileDataRow->ProjectileData.InitialSpeed;
    ProjectileMovement->MaxSpeed = ProjectileDataRow->ProjectileData.MaxSpeed;
    ProjectileMovement->bRotationFollowsVelocity = true;
    ProjectileMovement->bShouldBounce = false;

    if (ProjectileDataRow != nullptr)
    {
        UStaticMesh* StaticMesh = ProjectileDataRow->StaticMesh.LoadSynchronous();
        
    }
}

// Called every frame
void AEnemyProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

