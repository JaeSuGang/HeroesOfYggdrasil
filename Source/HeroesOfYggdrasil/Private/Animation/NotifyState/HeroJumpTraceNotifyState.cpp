// Coded By AssortRock Unreal Engine Class Project


#include "Animation/NotifyState/HeroJumpTraceNotifyState.h"

#include "Player/YggHero.h"

#include "Kismet/KismetMathLibrary.h"  // Kismet Math Library 사용
#include "Math/UnrealMathUtility.h"  // Unreal Math Utility 사용






void UHeroJumpTraceNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);

	AYggHero* Hero = Cast<AYggHero>(MeshComp->GetOwner());
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
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("StartLocation : %s, TargetLocation : %s"), *StartLocation.ToString(),*TargetLocation.ToString()));
		Hero->Jump();
	}
	



}

void UHeroJumpTraceNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	AYggHero* Hero = Cast<AYggHero>(MeshComp->GetOwner());
	if (IsValid(Hero))
	{
		
	}
}

void UHeroJumpTraceNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
}
