// Coded By AssortRock Unreal Engine Class Project


#include "Global/YggProjectileActor.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"

#include "Core/YggCharacter.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AYggProjectileActor::AYggProjectileActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	AttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("AttackCapsuleComponent"));
	AttackCapsuleComponent->SetupAttachment(RootComponent);

}

// Called when the game starts or when spawned
void AYggProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(OwnerCharacter))
	{
		AttackCapsuleComponent->SetOwnerCharacter(OwnerCharacter);
		AttackCapsuleComponent->CollisionOn();
	}
	ProjectileDataRow = *ProjectileData->FindRow<FSpawnProjectileDataRow>(RowName, nullptr);
	ProjectileType = ProjectileDataRow.ProjectileType;
	ProjectileMovement->InitialSpeed = ProjectileDataRow.InitialSpeed;
	ProjectileMovement->MaxSpeed = ProjectileDataRow.MaxSpeed;
	ProjectileMovement->Velocity = AimDirection * ProjectileDataRow.InitialSpeed;
	



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
	
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			Destroy();
		}, ProjectileDataRow.DestroyTime, false);
}

// Called every frame
void AYggProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	DrawDebugSphere(GetWorld(), GetActorLocation(), 10.f, 12, FColor::Red);
}

void AYggProjectileActor::SetAimDir(FVector _AimDirection)
{
	AimDirection = _AimDirection;
}

void AYggProjectileActor::LineMode()
{
	// 이동 방향으로 Velocity 설정
	
	ProjectileMovement->ProjectileGravityScale = 0.f;
}

void AYggProjectileActor::ParabolaMode()
{
	ProjectileMovement->Velocity += FVector(0.f, 0.f, ProjectileDataRow.Height);
	ProjectileMovement->ProjectileGravityScale = 1.f;
}

void AYggProjectileActor::TargetParabolaMode()
{
	if (!ProjectileMovement) return;

	FVector StartLocation = GetActorLocation();
	FVector TossVelocity;

	// 고정된 발사 속도로 포물선 궤적 계산
	bool bHasSolution = UGameplayStatics::SuggestProjectileVelocity_CustomArc(
		this,
		TossVelocity,
		StartLocation,
		TargetLocation,
		0.5f // Arc parameter: 0.0 = flat shot, 1.0 = high arc (0.5은 보통 느낌)
	);

	if (bHasSolution)
	{
		ProjectileMovement->Velocity += TossVelocity;
	}
}

void AYggProjectileActor::HomingMode()
{
}



