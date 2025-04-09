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
	APlayerController* PC = GetWorld()->GetFirstPlayerController();
	if (!PC) return;

	FVector CamLoc;
	FRotator CamRot;
	PC->GetPlayerViewPoint(CamLoc, CamRot);

	FVector AimDirection = CamRot.Vector();

	// 내 위치 기준으로 방향 설정
	FVector ToAim = AimDirection;
	FRotator AimRot = ToAim.Rotation();

	SetActorRotation(AimRot);

	// 이동 방향으로 Velocity 설정
	ProjectileMovement->Velocity = AimDirection * ProjectileDataRow.InitialSpeed;
	ProjectileMovement->ProjectileGravityScale = 0.f;
	ProjectileMovement->InitialSpeed = ProjectileDataRow.InitialSpeed;
	ProjectileMovement->MaxSpeed = ProjectileDataRow.MaxSpeed;
}

void AYggProjectileActor::ParabolaMode()
{
	ProjectileMovement->Velocity += FVector(0.f, 0.f, ProjectileDataRow.Height);
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



