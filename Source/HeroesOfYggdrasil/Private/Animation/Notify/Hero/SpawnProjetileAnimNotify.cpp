// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Hero/SpawnProjetileAnimNotify.h"

#include "Core/YggCharacter.h"
#include "Global/YggProjectileActor.h"
#include "Player/YggHero.h"
#include "Kismet/GameplayStatics.h"
#include "Player/YggHeroRevenant.h"
void USpawnProjetileAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp || !ProjectileClass) return;

	AYggCharacter* Actor = Cast<AYggCharacter>(MeshComp->GetOwner());
	if (!IsValid(Actor)) return;
	if ((Actor->HasAuthority()))
	{

		{
			const FVector SpawnLocation = Actor->GetMesh()->GetSocketLocation(SocketName);
			const FVector AimDirection = Cast<AYggHero>(Actor)->GetAimDirection();
			const FRotator AimRot = AimDirection.Rotation();

			FTransform SpawnTransform(AimRot, SpawnLocation);

			AYggProjectileActor* Projectile = MeshComp->GetWorld()->SpawnActorDeferred<AYggProjectileActor>(
				ProjectileClass,
				SpawnTransform,
				Actor,
				nullptr,
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);

			if (!Projectile) return;

			Projectile->SetOwnerCharacter(Actor);
			UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);
			Projectile->SetAimDir(AimDirection);
		}

		if (AYggHeroRevenant* Revenant = Cast<AYggHeroRevenant>(Actor))
		{
			if (Revenant->GetIsUsingSkillR())
			{
				{
					const FVector SpawnLocation = Actor->GetMesh()->GetSocketLocation(TEXT("R_Pos_Left"));
					const FVector AimDirection = Cast<AYggHero>(Actor)->GetAimDirection();
					const FRotator AimRot = AimDirection.Rotation();

					FTransform SpawnTransform(AimRot, SpawnLocation);

					AYggProjectileActor* Projectile = MeshComp->GetWorld()->SpawnActorDeferred<AYggProjectileActor>(
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

				{
					const FVector SpawnLocation = Actor->GetMesh()->GetSocketLocation(TEXT("R_Pos_Right"));
					const FVector AimDirection = Cast<AYggHero>(Actor)->GetAimDirection();
					const FRotator AimRot = AimDirection.Rotation();

					FTransform SpawnTransform(AimRot, SpawnLocation);

					AYggProjectileActor* Projectile = MeshComp->GetWorld()->SpawnActorDeferred<AYggProjectileActor>(
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

			}
		}



	}


}

