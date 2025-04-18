// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Hero/SpawnProjetileAnimNotify.h"

#include "Core/YggCharacter.h"
#include "Global/YggProjectileActor.h"
#include "Player/YggHeroRevenant.h"
#include "Kismet/GameplayStatics.h"
void USpawnProjetileAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (!MeshComp || !ProjectileClass) return;

	AYggCharacter* Actor = Cast<AYggCharacter>(MeshComp->GetOwner());
	if (!IsValid(Actor)) return;

	if (!Actor->HasAuthority()) return;	

	const FVector SpawnLocation = Actor->GetMesh()->GetSocketLocation(SocketName);
	const FVector AimDirection = Cast<AYggHeroRevenant>(Actor)->AimDirection;
	const FRotator AimRot = AimDirection.Rotation();

	FTransform SpawnTransform(AimRot, SpawnLocation);

	AYggProjectileActor* Projectile = GetWorld()->SpawnActorDeferred<AYggProjectileActor>(
		ProjectileClass,
		SpawnTransform,
		Actor,
		nullptr,
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
	);

	if (!Projectile) return;

	Projectile->SetOwnerCharacter(Actor);
	Projectile->SetAimDir(AimDirection);

	UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
}

