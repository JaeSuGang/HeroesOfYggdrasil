// Coded By AssortRock Unreal Engine Class Project


#include "Global/YggProjectileActor.h"
#include "GameFramework/ProjectileMovementComponent.h"

#include "Kismet/GameplayStatics.h"

// Sets default values
AYggProjectileActor::AYggProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
}

// Called when the game starts or when spawned
void AYggProjectileActor::BeginPlay()
{
	Super::BeginPlay();

	ProjectileDataRow = *ProjectileData->FindRow<FSpawnProjectileDataRow>(RowName, nullptr);
	ProjectileType = ProjectileDataRow.ProjectileType;

	switch (ProjectileType)
	{
	case EProjectileType::Line:
		LineMode();
		break;
	case EProjectileType::Parabola:
		ParabolaMode();
		break;
	case EProjectileType::TargetParabola:
		TargetParabolaMode();
		break;
	case EProjectileType::Homing:
		HomingMode();
		break;
	default:
		break;
	}

}

// Called every frame
void AYggProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), GetActorLocation(), 10.f, 12, FColor::Red);
}

void AYggProjectileActor::LineMode()
{
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->InitialSpeed = ProjectileDataRow.InitialSpeed;
	ProjectileMovement->MaxSpeed = ProjectileDataRow.MaxSpeed;
}

void AYggProjectileActor::ParabolaMode()
{
	FRotator Rotation = GetActorRotation();
	Rotation.Pitch += ProjectileDataRow.Angle;
	SetActorRotation(Rotation);
	ProjectileMovement->InitialSpeed = ProjectileDataRow.InitialSpeed;
	ProjectileMovement->MaxSpeed = ProjectileDataRow.MaxSpeed;
	ProjectileMovement->ProjectileGravityScale = 1.f;
	
}

void AYggProjectileActor::TargetParabolaMode()
{
	
}

void AYggProjectileActor::HomingMode()
{
}



