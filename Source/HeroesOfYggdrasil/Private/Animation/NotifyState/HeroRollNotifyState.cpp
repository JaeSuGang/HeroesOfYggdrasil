// Coded By AssortRock Unreal Engine Class Project


#include "Animation/NotifyState/HeroRollNotifyState.h"
#include "Animation/HeroGreystoneAnimInstance.h"
#include "Player/YggHeroGreystone.h"
#include "Attribute/HeroAttributeComponent.h"
#include "GameFramework/CharacterMovementComponent.h"

void UHeroRollNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
}

void UHeroRollNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	if (!MeshComp || !MeshComp->GetOwner()) return;

	AYggHeroGreystone* Greystone = Cast<AYggHeroGreystone>(MeshComp->GetOwner());
	if (!Greystone) return;

	const float RollSpeed = 1200.0f;
	FVector RollDirection = Greystone->GetActorForwardVector();
	FVector Movement = RollDirection * RollSpeed * FrameDeltaTime;

	if (UCharacterMovementComponent* MoveComp = Greystone->GetCharacterMovement())
	{
		MoveComp->Velocity = Movement / FrameDeltaTime;
	}

	UHeroGreystoneAnimInstance* AnimInstance = Cast<UHeroGreystoneAnimInstance>(MeshComp->GetAnimInstance());
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
	UHeroGreystoneAnimInstance* AnimInstance = Cast<UHeroGreystoneAnimInstance>(MeshComp->GetAnimInstance());
	if (!AnimInstance) return;

	AnimInstance->bIsRoll = false;

	AYggHeroGreystone* Greystone = Cast<AYggHeroGreystone>(MeshComp->GetOwner());
	if (!Greystone) return;

	Greystone->GetHeroAttributeComponent()->RemoveTag(TEXT("Character.State.NotRollable"));
	Greystone->GetHeroAttributeComponent()->RemoveTag(TEXT("Character.State.NotMoveable"));
}
