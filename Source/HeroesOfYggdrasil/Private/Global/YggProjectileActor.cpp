// Coded By AssortRock Unreal Engine Class Project


#include "Global/YggProjectileActor.h"

#include "GameFramework/ProjectileMovementComponent.h"
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"

#include "Net/UnrealNetwork.h"

#include "Core/YggCharacter.h"
#include "Kismet/GameplayStatics.h"


// Sets default values
AYggProjectileActor::AYggProjectileActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	

	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->SetIsReplicated(true);

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	AttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("AttackCapsuleComponent"));
	AttackCapsuleComponent->SetupAttachment(RootComponent);
	//AttackCapsuleComponent->PlusLogic.AddDynamic(this, &AYggProjectileActor::StartDestroy);
}

// Called when the game starts or when spawned
void AYggProjectileActor::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AYggProjectileActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!bIsInit)
	{
		SetInit();
	}
	CurTime += DeltaTime;
	if (CurTime >= ProjectileDataRow.DestroyTime)
	{
		Destroy();
	}
}

void AYggProjectileActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AYggProjectileActor, AimDirection);
	DOREPLIFETIME(AYggProjectileActor, ProjectileMovement);
	
}

void AYggProjectileActor::SetAimDir(FVector _AimDirection)
{

	if (HasAuthority())
	{
		MultiCast_SetAimDir(_AimDirection);
	}
	else
	{
		Server_SetAimDir(_AimDirection);
	}
}

void AYggProjectileActor::SetInit()
{
	if (HasAuthority())
	{
		MultiCast_SetInit();
	}
	else
	{
		Server_SetInit();
	}
}


void AYggProjectileActor::Server_SetInit_Implementation()
{
	MultiCast_SetInit();
	
	
	bIsInit = true;
}

void AYggProjectileActor::MultiCast_SetInit_Implementation()
{
	if (IsValid(OwnerCharacter))
	{
		AttackCapsuleComponent->SetOwnerCharacter(OwnerCharacter);
		AttackCapsuleComponent->CollisionOn();
	}
	if (ProjectileMovement)
	{
		ProjectileDataRow = *ProjectileData->FindRow<FSpawnProjectileDataRow>(RowName, nullptr);
		ProjectileType = ProjectileDataRow.ProjectileType;
		ProjectileMovement->MaxSpeed = ProjectileDataRow.MaxSpeed;
		ProjectileMovement->Velocity = AimDirection * ProjectileDataRow.InitialSpeed;
		ProjectileMovement->InitialSpeed = ProjectileDataRow.InitialSpeed;
	}
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
	bIsInit = true;
}

void AYggProjectileActor::Server_SetAimDir_Implementation(FVector _AimDirection)
{
	AimDirection = _AimDirection;
	MultiCast_SetAimDir(AimDirection);
}

void AYggProjectileActor::MultiCast_SetAimDir_Implementation(FVector _AimDirection)
{
	AimDirection = _AimDirection;
}

void AYggProjectileActor::SetHomingTarget(AActor* Target)
{
}

void AYggProjectileActor::StartDestroy()
{
	AttackCapsuleComponent->CollisionOff();
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

}

void AYggProjectileActor::HomingMode()
{

}



