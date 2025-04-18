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

			// 카메라 시점에서 조준 방향을 얻는 것이 아니라, 카메라 방향으로 레이캐스트하여 충돌 위치를 목표로 삼는다
			FVector CamLoc;
			FRotator CamRot;
			PC->GetPlayerViewPoint(CamLoc, CamRot);

			// 카메라 방향으로 먼 거리까지 트레이스
			FVector TraceEnd = CamLoc + CamRot.Vector() * 10000.f;

			FHitResult HitResult;
			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(Actor);

			bool bHit = GetWorld()->LineTraceSingleByChannel(HitResult, CamLoc, TraceEnd, ECC_Visibility, QueryParams);

			// 명중 지점 또는 카메라 방향 끝을 타겟으로 설정
			FVector TargetLocation = bHit ? HitResult.ImpactPoint : TraceEnd;

			// "소켓 위치 → 목표 위치" 방향을 투사체 방향으로 설정
			FVector AimDirection = (TargetLocation - SpawnLocation).GetSafeNormal();
			FRotator AimRot = AimDirection.Rotation();

			Projectile->SetActorRotation(AimRot);
			Projectile->SetAimDir(AimDirection);

			// 이제 BeginPlay 등 초기화가 실행됨
			UGameplayStatics::FinishSpawningActor(Projectile, SpawnTransform);

		}
	}
}

