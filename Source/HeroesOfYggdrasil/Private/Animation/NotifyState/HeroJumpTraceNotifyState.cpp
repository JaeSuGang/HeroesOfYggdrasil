// Coded By AssortRock Unreal Engine Class Project


#include "Animation/NotifyState/HeroJumpTraceNotifyState.h"

#include "Player/YggHero.h"

#include "Kismet/KismetMathLibrary.h"  // Kismet Math Library 사용
#include "Math/UnrealMathUtility.h"  // Unreal Math Utility 사용

#include "Animation/YggHeroAnimInstance.h"

#include "GameFramework/CharacterMovementComponent.h"





void UHeroJumpTraceNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	ElapsedTime = 0.0f;
	Hero = Cast<AYggHero>(MeshComp->GetOwner());
	if (IsValid(Hero))
	{
		StartLocation = Hero->GetActorLocation();
		MoveDuration = EventReference.GetNotify()->GetDuration();
		bool bIsAimMode = Hero->IsAimMode();

		FHitResult HitResult;
		FCollisionQueryParams QueryParams;
		QueryParams.AddIgnoredActor(Hero);
		FCollisionObjectQueryParams ObjectQueryParams;
		ObjectQueryParams.AddObjectTypesToQuery(ECC_GameTraceChannel1);
		bool bIsHit = Hero->GetWorld()->SweepSingleByObjectType(HitResult, StartLocation, StartLocation, FQuat::Identity, ObjectQueryParams, FCollisionShape::MakeSphere(1000), QueryParams);
		if (true == bIsHit)
		{
			AActor* HitActor = HitResult.GetActor();
			TargetLocation = HitActor->GetActorLocation();
		}
		else if (false == bIsHit)
		{
			TargetLocation = StartLocation + Hero->GetActorForwardVector() * 1000;
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
		FVector TargetPos = FMath::Lerp(StartLocation, TargetLocation, Alpha);

		// ★ 포물선 곡선
		float JumpCurve = 4 * Alpha * (1 - Alpha);
		TargetPos.Z += JumpHeight * JumpCurve;

		// 이동량 계산
		FVector CurrentLocation = Hero->GetActorLocation();
		FVector Delta = TargetPos - CurrentLocation;

		// 방향 보정
		FVector Direction = Delta;
		Direction.Z = 0.0f;
		if (!Direction.IsNearlyZero())
		{
			FRotator TargetRotation = Direction.Rotation();
			Hero->SetActorRotation(TargetRotation);
		}

		// 위치를 Delta만큼만 이동
		Hero->AddActorWorldOffset(Delta, true);
	}
}

void UHeroJumpTraceNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	ElapsedTime = 0.0f;
}
