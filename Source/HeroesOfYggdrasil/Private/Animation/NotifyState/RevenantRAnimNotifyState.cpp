// Coded By AssortRock Unreal Engine Class Project


#include "Animation/NotifyState/RevenantRAnimNotifyState.h"
#include "Kismet/GameplayStatics.h"
#include "Core/YggCharacter.h"
#include "Global/YggProjectileActor.h"
#include "Player/YggHeroRevenant.h"
#include "Player/YggHero.h"

void URevenantRAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	if (!MeshComp || !ActorClass) {
		return;
	}
	AYggCharacter* Actor = Cast<AYggCharacter>(MeshComp->GetOwner());
	if (!IsValid(Actor)) return;
	if ((Actor->HasAuthority())) 
	{
		{
			const FVector  SpawnLocation = Actor->GetMesh()->GetSocketLocation(TEXT("R_Pos_Left"));
			const FRotator SpawnRotation = FRotator::ZeroRotator;   // 필요-없으면 0 으로

			FActorSpawnParameters Params;
			Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

			

			AActor* Spawned =
				MeshComp->GetWorld()->SpawnActor<AActor>(ActorClass,
					SpawnLocation,
					SpawnRotation,
					Params);
			Spawned->AttachToActor(Actor, FAttachmentTransformRules::KeepWorldTransform);

			FTimerHandle TimerHandle;
			TWeakObjectPtr<AActor> WeakSpawned = Spawned;          
			Actor->GetWorld()->GetTimerManager().SetTimer(
				TimerHandle,                                       
				[WeakSpawned, Actor]()
				{
					if (WeakSpawned.IsValid())
					{
						WeakSpawned->Destroy();
					}
					if (AYggHeroRevenant* Revenant = Cast<AYggHeroRevenant>(Actor)) 
					{
					Revenant->SetIsUsingSkillR(false);
					}
					
				},
				10.0f,                                              
				false                                              
			);

		}
		{
			const FVector  SpawnLocation = Actor->GetMesh()->GetSocketLocation(TEXT("R_Pos_Right"));
			const FRotator SpawnRotation = FRotator::ZeroRotator;   // 필요-없으면 0 으로

			FActorSpawnParameters Params;
			Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;



			AActor* Spawned =
				MeshComp->GetWorld()->SpawnActor<AActor>(ActorClass,
					SpawnLocation,
					SpawnRotation,
					Params);
			Spawned->AttachToActor(Actor, FAttachmentTransformRules::KeepWorldTransform);
			FTimerHandle TimerHandle;
			TWeakObjectPtr<AActor> WeakSpawned = Spawned;
			Actor->GetWorld()->GetTimerManager().SetTimer(
				TimerHandle,
				[WeakSpawned]()
				{
					if (WeakSpawned.IsValid())
					{
						WeakSpawned->Destroy();
					}
				},
				10.0f,
				false
			);
		}
	}

	
}

void URevenantRAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	
	
}

void URevenantRAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	//CurCount = 0;
	
}
