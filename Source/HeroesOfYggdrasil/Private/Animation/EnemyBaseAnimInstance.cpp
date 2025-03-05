// Coded By AssortRock Unreal Engine Class Project


#include "Animation/EnemyBaseAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Attribute/AttributeComponent.h"
#include "Enemy/EnemyCharacter.h"

void UEnemyBaseAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Enemy = Cast<AEnemyCharacter>(TryGetPawnOwner());
	if (Enemy == nullptr)
	{
		return;
	}
	CharacterMovementComponent = Enemy->GetCharacterMovement();
}

void UEnemyBaseAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaTime)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaTime);
	if (CharacterMovementComponent == nullptr)
	{
		return;
	}

	GroundSpeed = UKismetMathLibrary::VSizeXY(CharacterMovementComponent->Velocity);
	LocomotionDirection = CalculateDirection(CharacterMovementComponent->Velocity, Enemy->GetActorRotation());
}

bool UEnemyBaseAnimInstance::NativeDoesActorHaveTag(AActor* InActor, FGameplayTag TagToCheck)
{
	int a = 0;

	if (InActor)
	{
		FString ActorName = InActor->GetName();
		FString ActorNameLeft = ActorName.Left(8);

		FName TagName = TagToCheck.GetTagName();

		if (ActorNameLeft == FString("BP_Enemy") && TagName == FName("Monster.State.Strafing"))
		{
			return true;
		}
	}
	
	return false;
}

bool UEnemyBaseAnimInstance::OwnerHaveTag(FGameplayTag _TagToCheck)
{
	if (APawn* OwningPawn = TryGetPawnOwner())
	{
		return NativeDoesActorHaveTag(OwningPawn, _TagToCheck);
	}
	else
	{
		return false;
	}
}

