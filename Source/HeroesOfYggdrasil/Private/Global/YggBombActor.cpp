// Coded By AssortRock Unreal Engine Class Project


#include "Global/YggBombActor.h"
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"

AYggBombActor::AYggBombActor()
{
	ExplosionAttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("ExplosionAttackCapsuleComponent"));
	ExplosionAttackCapsuleComponent->SetupAttachment(RootComponent);
	ProjectileType = EProjectileType::TargetParabola;

}

void AYggBombActor::ExplosionOn()
{
	ExplosionAttackCapsuleComponent->CollisionOn();
}

void AYggBombActor::BeginPlay()
{
	Super::BeginPlay();
	if (OwnerCharacter)
	{
		ExplosionAttackCapsuleComponent->SetOwnerCharacter(OwnerCharacter);
	}
	AttackCapsuleComponent->PlusLogic.AddDynamic(this, &AYggBombActor::ExplosionOn);
}
