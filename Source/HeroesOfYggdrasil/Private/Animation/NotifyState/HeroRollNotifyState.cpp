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

	const float RollSpeed = 1000.0f; // 초당 이동 거리
	FVector RollDirection = Greystone->GetActorForwardVector();
	FVector Movement = RollDirection * RollSpeed * FrameDeltaTime;

	if (UCharacterMovementComponent* MoveComp = Greystone->GetCharacterMovement())
	{
		MoveComp->Velocity = Movement / FrameDeltaTime;
	}

	/*UHeroGreystoneAnimInstance* AnimInstance = Cast<UHeroGreystoneAnimInstance>(MeshComp->GetAnimInstance());
	if (!AnimInstance) return;

	float MontageSpeed = AnimInstance->Montage_GetPlayRate(AnimInstance->GetCurrentActiveMontage());
	MontageSpeed -= FrameDeltaTime * 50.0f;
	AnimInstance->Montage_SetPlayRate(AnimInstance->GetCurrentActiveMontage(), MontageSpeed);*/
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
