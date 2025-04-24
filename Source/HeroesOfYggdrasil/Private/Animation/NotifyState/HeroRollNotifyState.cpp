// Coded By AssortRock Unreal Engine Class Project


#include "Animation/NotifyState/HeroRollNotifyState.h"
#include "Animation/YggHeroAnimInstance.h"

#include "Player/YggHero.h"

#include "Attribute/HeroAttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"

void UHeroRollNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
}

void UHeroRollNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp || !MeshComp->GetOwner()) return;

	AYggHero* Hero = Cast<AYggHero>(MeshComp->GetOwner());
	if (!Hero) return;

	const float RollSpeed = Hero->GetHeroAttributeComponent()->MaxMoveSpeed * RollRate;
	FVector RollDirection = Hero->GetActorForwardVector();
	FVector Movement = RollDirection * RollSpeed * FrameDeltaTime;

	if (UCharacterMovementComponent* MoveComp = Hero->GetCharacterMovement())
	{
		MoveComp->Velocity = Movement / FrameDeltaTime;
	}

	UYggHeroAnimInstance* AnimInstance = Cast<UYggHeroAnimInstance>(MeshComp->GetAnimInstance());
	if (!AnimInstance) return;
	UAnimMontage* CurrentMontage = AnimInstance->GetCurrentActiveMontage();
	if (!CurrentMontage) return;

	float CurrentSpeed = AnimInstance->Montage_GetPlayRate(CurrentMontage);
	float NewSpeed = FMath::Lerp(CurrentSpeed, 0.5f, FrameDeltaTime * 5.0f);
	NewSpeed = FMath::Clamp(NewSpeed, 0.5f, 1.0f);

	AnimInstance->Montage_SetPlayRate(CurrentMontage, NewSpeed);
}

void UHeroRollNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp || !MeshComp->GetOwner()) return;
	UYggHeroAnimInstance* AnimInstance = Cast<UYggHeroAnimInstance>(MeshComp->GetAnimInstance());
	if (!AnimInstance) return;

	AnimInstance->bIsRoll = false;

	AYggHero* Hero = Cast<AYggHero>(MeshComp->GetOwner());
	if (!Hero) return;

	//Hero->GetHeroAttributeComponent()->RemoveTag(TEXT("Character.State.NotRollable"));
	Hero->GetHeroAttributeComponent()->RemoveTag(TEXT("Character.State.NotMoveable"));
	Hero->GetHeroAttributeComponent()->RemoveTag(TEXT("Character.State.NotAttackable"));

	if (Hero->GetHeroAttributeComponent()->HasTagExact(TEXT("Character.State.PressedAttack")))
		Hero->Attack(FInputActionValue());
}
