// Coded By AssortRock Unreal Engine Class Project


#include "Animation/Notify/Hero/GetTargetActorAnimNotify.h"
#include "Core/YggCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "Global/YggBombActor.h"

void UGetTargetActorAnimNotify::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);


	if (BombClass)
	{
		AYggCharacter* Actor = Cast<AYggCharacter>(MeshComp->GetOwner());
		if (IsValid(Actor))
		{
			FVector SpawnLocation = Actor->GetMesh()->GetSocketLocation(SocketName);
			FRotator InitialRotation = FRotator::ZeroRotator; // 초기에는 임의의 Rotation 사용
			FTransform SpawnTransform(InitialRotation, SpawnLocation);

			// 디퍼드 스폰: BeginPlay가 아직 호출되지 않음
			AYggBombActor* Bomb = GetWorld()->SpawnActorDeferred<AYggBombActor>(
				BombClass,
				SpawnTransform,
				Actor, // Owner
				nullptr, // Instigator
				ESpawnActorCollisionHandlingMethod::AlwaysSpawn
			);

			if (!Bomb) return;

			// 필요 설정들 적용
			Bomb->SetOwnerCharacter(Actor);

			APlayerController* PC = GetWorld()->GetFirstPlayerController();
			if (!PC) return;

			FVector CamLoc;
			FRotator CamRot;
			PC->GetPlayerViewPoint(CamLoc, CamRot);

			FVector AimDirection = CamRot.Vector();
			FRotator AimRot = AimDirection.Rotation();

			// 원하는 방향으로 설정
			Bomb->SetActorRotation(AimRot);
			Bomb->SetAimDir(AimDirection);

			FHitResult HitResult;
			FVector EndLocation = SpawnLocation + AimDirection * Scope;

			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(Actor);
			QueryParams.bTraceComplex = true;

			FCollisionObjectQueryParams ObjectQueryParams;
			ObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel1); // 적 캐릭터가 이 채널이어야 함

			FVector BoxHalfSize(50.f, 50.f, 50.f);
			FRotator Orientation = (EndLocation - SpawnLocation).Rotation();

			bool bIsHit = GetWorld()->SweepSingleByObjectType(
				HitResult,
				SpawnLocation,
				EndLocation,
				FQuat(Orientation),
				ObjectQueryParams,
				FCollisionShape::MakeBox(BoxHalfSize),
				QueryParams
			);

			FVector TargetLocation = bIsHit ? HitResult.GetActor()->GetActorLocation() : EndLocation;

			// Bomb에 전달
			Bomb->SetActorRotation(AimRot);
			Bomb->SetAimDir(AimDirection);
			Bomb->SetTargetLocation(TargetLocation); // 필요 시 함수로 전달

			// 이제 BeginPlay 등 초기화가 실행됨
			UGameplayStatics::FinishSpawningActor(Bomb, SpawnTransform);
		}
	}

}
