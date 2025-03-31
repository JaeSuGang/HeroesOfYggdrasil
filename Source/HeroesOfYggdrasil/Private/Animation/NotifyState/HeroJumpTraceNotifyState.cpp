// Coded By AssortRock Unreal Engine Class Project


#include "Animation/NotifyState/HeroJumpTraceNotifyState.h"

#include "Player/YggHero.h"

#include "Kismet/KismetMathLibrary.h"  // Kismet Math Library 사용
#include "Math/UnrealMathUtility.h"  // Unreal Math Utility 사용

#include "GameFramework/CharacterMovementComponent.h"





void UHeroJumpTraceNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	ElapsedTime = 0.0f;
	Hero = Cast<AYggHero>(MeshComp->GetOwner());
	if (IsValid(Hero))
	{
		StartLocation = Hero->GetActorLocation();
		bool bIsAimMode = Hero->IsAimMode();
		if (bIsAimMode)
		{

		}

		else
		{
			FHitResult HitResult;
			FCollisionQueryParams QueryParams;
			QueryParams.AddIgnoredActor(Hero);
			FCollisionObjectQueryParams ObjectQueryParams;
			ObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel1);
			bool bIsHit = Hero->GetWorld()->SweepSingleByObjectType(HitResult, StartLocation, StartLocation, FQuat::Identity, ObjectQueryParams, FCollisionShape::MakeSphere(1000), QueryParams);
			if (true ==bIsHit)
			{
				AActor* HitActor = HitResult.GetActor();
				TargetLocation = HitActor->GetActorLocation();
			}
			else if (false == bIsHit)
			{
				TargetLocation = StartLocation;
			}
		}
	}
}

void UHeroJumpTraceNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	
	if (IsValid(Hero))
	{
		ElapsedTime += FrameDeltaTime;

		float Alpha = FMath::Clamp(ElapsedTime / MoveDuration, 0.0f, 1.0f);
		FVector NewLocation = FMath::Lerp(StartLocation, TargetLocation, Alpha);

		FVector Direction = (TargetLocation - NewLocation);
		Direction.Z = 0.0f; // 평면(2D) 이동 시 Z축 회전 제거
		if (!Direction.IsNearlyZero())
		{
			FRotator TargetRotation = Direction.Rotation();
			Hero->SetActorRotation(TargetRotation);
		}

		Hero->SetActorLocation(NewLocation);
	}
}

void UHeroJumpTraceNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ElapsedTime = 0.0f;
}
