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

void UEnemyBaseAnimInstance::ChangeAnimation(EEnemyAIState _CurAnimationType, FName _SectionName)
{
	if (false == AnimMontages.Contains(static_cast<int>(_CurAnimationType)))
	{
		return;
	}

	UAnimMontage* Montage = AnimMontages[static_cast<int>(_CurAnimationType)];

	if (CurMontage == Montage)
	{
		if (SectionName != _SectionName)
		{
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


