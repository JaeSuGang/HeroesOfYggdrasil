// Coded By AssortRock Unreal Engine Class Project


#include "Global/YggBombActor.h"

#include "Particles/ParticleSystemComponent.h"

#include "Component/SceneComponent/YggAttackCapsuleComponent.h"

AYggBombActor::AYggBombActor()
{
	ExplosionAttackCapsuleComponent = CreateDefaultSubobject<UYggAttackCapsuleComponent>(TEXT("ExplosionAttackCapsuleComponent"));
	ExplosionAttackCapsuleComponent->SetupAttachment(RootComponent);
	ExplosionParticle = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("ExplosionParticle"));
	ExplosionParticle->SetupAttachment(RootComponent);
	ExplosionParticle->SetIsReplicated(true);
	ExplosionParticle->bAutoActivate = false;
}

void AYggBombActor::ExplosionOn()
{
	ExplosionAttackCapsuleComponent->CollisionOn();
	AttackCapsuleComponent->CollisionOff();
	if (HasAuthority())
	{
		NetMultiExplosionOn();
	}
	else
	{
		ServerExplosionOn();
	}
}
void AYggBombActor::ServerExplosionOn_Implementation()
{
	NetMultiExplosionOn();
}

void AYggBombActor::NetMultiExplosionOn_Implementation()
{
	ExplosionParticle->Activate(true);
}

void AYggBombActor::BeginPlay()
{
	Super::BeginPlay();
	if (OwnerCharacter)
	{
		ExplosionAttackCapsuleComponent->SetOwnerCharacter(OwnerCharacter);
	}
	AttackCapsuleComponent->PlusLogic.RemoveAll(this);
	AttackCapsuleComponent->PlusLogic.AddDynamic(this, &AYggBombActor::ExplosionOn);
}
