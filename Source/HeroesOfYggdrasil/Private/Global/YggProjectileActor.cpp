// Coded By AssortRock Unreal Engine Class Project


#include "Global/YggProjectileActor.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AYggProjectileActor::AYggProjectileActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement"));
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // 기본값, Parabola 타입에서만 바뀜

}

// Called when the game starts or when spawned
void AYggProjectileActor::BeginPlay()
{
	Super::BeginPlay();
	if (IsValid(OwnerActor))
	{
		SetActorRotation(OwnerActor->GetActorRotation());
	}
	const FVector Forward = GetActorForwardVector();

	switch (ProjectileType)
	{
	case EProjectileType::Line:
		ProjectileMovement->Velocity = Forward * Speed;
		ProjectileMovement->ProjectileGravityScale = 0.f;
		break;

	case EProjectileType::Parabola:
		ProjectileMovement->Velocity = Forward * Speed + FVector(0.f, 0.f, Height);
		ProjectileMovement->ProjectileGravityScale = 1.f; // 중력 적용
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

