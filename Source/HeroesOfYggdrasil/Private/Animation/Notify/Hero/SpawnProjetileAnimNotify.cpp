// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Hero/SpawnProjetileAnimNotify.h"

#include "Core/YggCharacter.h"
#include "Global/YggProjectileActor.h"
#include "Kismet/GameplayStatics.h"
void USpawnProjetileAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	if (ProjectileClass)
	{
		AYggCharacter* Actor = Cast<AYggCharacter>(MeshComp->GetOwner());
		if (IsValid(Actor))
		{
			FVector SpawnLocation = Actor->GetMesh()->GetSocketLocation(SocketName);
			FRotator InitialRotation = FRotator::ZeroRotator; // 초기에는 임의의 Rotation 사용
			FTransform SpawnTransform(InitialRotation, SpawnLocation);

			// 디퍼드 스폰: BeginPlay가 아직 호출되지 않음
			AYggProjectileActor* Projectile = GetWorld()->SpawnActorDeferred<AYggProjectileActor>(
				ProjectileClass,
				SpawnTransform,
				Actor, // Owner
				nullptr, // Instigator
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);

			if (!Projectile) return;

			// 필요 설정들 적용
			Projectile->SetOwnerCharacter(Actor);

			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			if (!PC) return;

			FVector CamLoc;
			FRotator CamRot;
			PC->GetPlayerViewPoint(CamLoc, CamRot);

			FVector AimDirection = CamRot.Vector();
			FRotator AimRot = AimDirection.Rotation();

			// 원하는 방향으로 설정
			Projectile->SetActorRotation(AimRot);
			Projectile->SetAimDir(AimDirection);

			// 이제 BeginPlay 등 초기화가 실행됨
			UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);

		}
	}
}

