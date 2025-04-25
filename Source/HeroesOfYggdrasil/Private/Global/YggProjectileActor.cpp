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
	SetReplicateMovement(true);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

	AttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("AttackCapsuleComponent"));
	AttackCapsuleComponent->SetupAttachment(RootComponent);
	AttackCapsuleComponent->PlusLogic.AddDynamic(this, &AYggProjectileActor::StartDestroy);
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
	//DrawDebugSphere(GetWorld(), GetActorLocation(), 10.f, 12, FColor::Red);
}

void AYggProjectileActor::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(AYggProjectileActor, AimDirection);
	DOREPLIFETIME(AYggProjectileActor, HomingTargetActor);
}

void AYggProjectileActor::SetAimDir(FVector _AimDirection)
{

	if (HasAuthority())
	{
		AimDirection = _AimDirection;
	}
	else
	{
		Server_SetAimDir(_AimDirection);
	}
}

void AYggProjectileActor::SetHomingTarget(AActor* Target)
{
	if (!HasAuthority())            // 서버 전용
		return;

	HomingTargetActor = Target;

	if (ProjectileMovement && Target)
	{
		ProjectileMovement->HomingTargetComponent = Target->GetRootComponent();
	}
}

void AYggProjectileActor::SetVelocity(FVector _Velocity)
{
	if (ProjectileMovement)
	{
		ProjectileMovement->Velocity = _Velocity;
	}
}

void AYggProjectileActor::SetInitialSpeed(float _InitialSpeed)
{
	if (ProjectileMovement)
	{
		ProjectileMovement->InitialSpeed = _InitialSpeed;
	}
}

void AYggProjectileActor::SetMaxSpeed(float _MaxSpeed)
{
	if (ProjectileMovement)
	{
		ProjectileMovement->MaxSpeed = _MaxSpeed;
	}
}

void AYggProjectileActor::DelayShoot(float _DelayTime)
{
	FTimerHandle TimerHandle;
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this]()
		{
			ComputeAndLaunch();
			AttackCapsuleComponent->CollisionOn();
		}, _DelayTime, false);
}

void AYggProjectileActor::Server_SetAimDir_Implementation(FVector _AimDirection)
{
	MultiCast_SetAimDir(_AimDirection);
}

void AYggProjectileActor::MultiCast_SetAimDir_Implementation(FVector _AimDirection)
{
	AimDirection = _AimDirection;
}

bool AYggProjectileActor::ComputeAndLaunch()
{
	const FVector Start = GetActorLocation();
	const FVector Target = TargetLocation;
	const double  g = FMath::Abs(GetWorld()->GetGravityZ());
	if (g < KINDA_SMALL_NUMBER) return false;

	const double ApexZ = bAbsoluteApexZ ? ApexOffsetZ
		: (Start.Z + ApexOffsetZ);
	const double HighestZ = FMath::Max(Start.Z, Target.Z);
	if (ApexZ <= HighestZ + 1.0) return false;

	/* ─── 포물선 3-식 ─── */
	const double Vz = FMath::Sqrt(2.0 * g * (ApexZ - Start.Z));
	const double tUp = Vz / g;
	const double tDown = FMath::Sqrt(2.0 * (ApexZ - Target.Z) / g);
	const double tTot = tUp + tDown;

	FVector ToTargetXY = Target - Start;  ToTargetXY.Z = 0;
	const double DistXY = ToTargetXY.Size();
	if (DistXY < KINDA_SMALL_NUMBER) return false;

	const FVector DirXY = ToTargetXY / DistXY;
	const double  Vxy = DistXY / tTot;

	const FVector LaunchVel = DirXY * Vxy + FVector(0, 0, Vz);

	/* ─── 바로 적용 & 발사 ─── */
	if (!ProjectileMovement) return false;

	ProjectileMovement->StopMovementImmediately();
	ProjectileMovement->Velocity = LaunchVel;
	ProjectileMovement->ProjectileGravityScale = 1.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->Activate(true);

	return true;
}

/*——— 발사 ———*/
void AYggProjectileActor::LaunchTo()
{

}

void AYggProjectileActor::StartDestroy()
{
	Destroy();
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
	// 중력은 대부분 끄지만 필요하면 DataRow에 따로 넣어도 됨
	ProjectileMovement->ProjectileGravityScale = 0.f;

	// 호밍 활성화
	ProjectileMovement->bIsHomingProjectile = true;

	// 가속도 크기: 데이터 테이블에 없으면 임의 상수나 MaxSpeed 기반으로 산출
	ProjectileMovement->HomingAccelerationMagnitude = FMath::Max(
		ProjectileDataRow.MaxSpeed * 10.f,               // 예시: 속도의 10배
		3000.f                                           // 최소값 보장
	);

	// ❶ 스폰 전에 SetHomingTarget()이 호출되어 타깃이 이미 정해진 경우
	if (HomingTargetActor.IsValid())
	{
		ProjectileMovement->HomingTargetComponent = HomingTargetActor->GetRootComponent();
		return;
	}

	// ❷ 타깃 액터가 아직 없지만 TargetLocation(월드 좌표)은 정해져 있는 경우
	//    – 임시 SceneComponent를 만들어 해당 좌표로 호밍
	if (!TargetLocation.IsNearlyZero())
	{
		USceneComponent* Dummy = NewObject<USceneComponent>(this, TEXT("DummyHomingTarget"));
		Dummy->RegisterComponent();
		Dummy->SetWorldLocation(TargetLocation);
		ProjectileMovement->HomingTargetComponent = Dummy;
		return;
	}

	// ❸ 둘 다 없으면 그냥 직진(또는 원하는 대로 처리)
	ProjectileMovement->bIsHomingProjectile = false;
}



