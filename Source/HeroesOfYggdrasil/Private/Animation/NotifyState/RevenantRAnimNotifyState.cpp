// Coded By AssortRock Unreal Engine Class Project


#include "Animation/NotifyState/RevenantRAnimNotifyState.h"
#include "Kismet/GameplayStatics.h"
#include "Core/YggCharacter.h"
#include "Global/YggProjectileActor.h"
#include "Player/YggHero.h"

void URevenantRAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}

void URevenantRAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	if (CurCount < Count)
	{
		ElapsedTime += FrameDeltaTime;
		if (ElapsedTime >= Delay)
		{
			if (!MeshComp || !ProjectileClass) return;

			AYggCharacter* Actor = Cast<AYggCharacter>(MeshComp->GetOwner());
			if (!IsValid(Actor)) return;
			if ((Actor->HasAuthority()))
			{
				FString SocketStr = FString::Printf(TEXT("FX_R_%d"), CurCount);
				const FVector SpawnLocation = Actor->GetMesh()->GetSocketLocation(*SocketStr);
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
				ProjectileList.Add(Projectile);
				GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Spawn_Projectile"));
				CurCount++;
			}
			ElapsedTime = 0.0f;
		}
	}
	
	
}

void URevenantRAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
