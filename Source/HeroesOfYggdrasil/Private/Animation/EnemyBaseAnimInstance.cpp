// Coded By AssortRock Unreal Engine Class Project


#include "Animation/EnemyBaseAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Attribute/AttributeComponent.h"
#include "Enemy/EnemyCharacter.h"



void UEnemyBaseAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();
	SkeletalMeshComponent = GetOwningComponent();
}

void UEnemyBaseAnimInstance::NativeUpdateAnimation(float _DeltaSeconds)
{
	Super::NativeUpdateAnimation(_DeltaSeconds);
}

void UEnemyBaseAnimInstance::ChangeAnimation(int _CurAnimationType, FName _SectionName)
{
	if (false == AnimMontages.Contains(_CurAnimationType))
	{
		return;
	}

	UAnimMontage* Montage = AnimMontages[_CurAnimationType];

	if (CurMontage == Montage)
	{
		if (SectionName != _SectionName)
		{
			// ChangeAnimationJumpEvent(Montage, _SectionName);
			Montage_Play(Montage);
			Montage_JumpToSection(_SectionName);
			SectionName = _SectionName;
		}

		return;
	}

	ChangeAnimationEvent(Montage, SectionName);

	CurMontage = Montage;
	CurAnimationType = _CurAnimationType;
	SectionName = _SectionName;
}




//void UEnemyBaseAnimInstance::NativeInitializeAnimation()
//{
//	Super::NativeInitializeAnimation();
//	Enemy = Cast<AEnemyCharacter>(TryGetPawnOwner());
//	if (Enemy == nullptr)
//	{
//		return;
//	}
//	CharacterMovementComponent = Enemy->GetCharacterMovement();
//}
//
//void UEnemyBaseAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaTime)
//{
//	Super::NativeThreadSafeUpdateAnimation(DeltaTime);
//	if (CharacterMovementComponent == nullptr)
//	{
//		return;
//	}
//	
//	GroundSpeed = UKismetMathLibrary::VSizeXY(CharacterMovementComponent->Velocity);
//
//	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
//	
//	if (PlayerController != nullptr)
//	{
//		ACharacter* MainCharacter = Cast<ACharacter>(PlayerController->GetPawn());
//		if (MainCharacter)
//		{
//			AActor* TargetActor = Cast<AActor>(MainCharacter);
//			APawn* OwningPawn = Cast<APawn>(Enemy);
//
//			if (OwningPawn && TargetActor)
//			{
//				FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(OwningPawn->GetActorLocation(), TargetActor->GetActorLocation());
//				FRotator TargetRot = FMath::RInterpTo(OwningPawn->GetActorRotation(), LookAtRot, DeltaTime, RotationInterSpeed);
//				LocomotionDirection = TargetRot.Yaw;
//			}
//		}
//	}
//}
//
//bool UEnemyBaseAnimInstance::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
//{
//	int a = 0;
//
//	if (InActor)
//	{
//		FString ActorName = InActor->GetName();
//		FString ActorNameLeft = ActorName.Left(8);
//
//		FName TagName = TagToCheck.GetTagName();
//
//		if (ActorNameLeft == FString("BP_Enemy") && TagName == FName("Monster.State.Strafing"))
//		{
//			return true;
//		}
//	}
//	
//	return false;
//}

//bool UEnemyBaseAnimInstance::OwnerHaveTag(FGameplayTag _TagToCheck)
//{
//	if (APawn* OwningPawn = TryGetPawnOwner())
//	{
//		return NativeDoesActorHaveTag(OwningPawn, _TagToCheck);
//	}
//	else
//	{
//		return false;
//	}
//}
