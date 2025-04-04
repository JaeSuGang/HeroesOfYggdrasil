// Coded By AssortRock Unreal Engine Class Project


#include "Animation/NotifyState/SetColllisionAnimNotifyState.h"
#include "Core/YggCharacter.h"
#include "Component/SceneComponent/YggAttackCapsuleComponent.h"
#include "Player/YggHero.h"
#include "Enemy/EnemyCharacter.h"
#include "Attribute/HeroAttributeComponent.h"

void USetColllisionAnimNotifyState::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
	AYggCharacter* YggCharacter = Cast<AYggCharacter>(MeshComp->GetOwner());
	if (YggCharacter)
	{
		UYggAttackCapsuleComponent* CapsuleComponent = YggCharacter->GetAttackCapsuleComponent(CollisionMapKey);
		if (CapsuleComponent)
		{
			CapsuleComponent->CollisionOn();
			CapsuleComponent->SetOwnerCharacter(YggCharacter);
		}
	}
}

void USetColllisionAnimNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);

}

void USetColllisionAnimNotifyState::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);

	AYggCharacter* YggCharacter = Cast<AYggCharacter>(MeshComp->GetOwner());
	if (!YggCharacter) return;

	if (!bEndWithTimer)
	{
		UYggAttackCapsuleComponent* CapsuleComponent = YggCharacter->GetAttackCapsuleComponent(CollisionMapKey);
		if (CapsuleComponent)
		{
			CapsuleComponent->CollisionOff();
		}
	}
	else
	{
		AYggHero* Hero = Cast<AYggHero>(YggCharacter);

		if (Hero)
		{
			if (CollisionMapKey == "SkillQAttack")
			{
				Duration = Hero->GetHeroAttributeComponent()->SkillQMaxContinueTime;

			}
			else if (CollisionMapKey == "SkillEAttack")
			{
				Duration = Hero->GetHeroAttributeComponent()->SkillEMaxContinueTime;
			}
			else if (CollisionMapKey == "SkillRAttack")
			{
				Duration = Hero->GetHeroAttributeComponent()->SkillRMaxContinueTime;
			}
		}
		
		FTimerHandle TimerHandle;
		MeshComp->GetWorld()->GetTimerManager().SetTimer(TimerHandle, [this, MeshComp, YggCharacter]()
		{
			UYggAttackCapsuleComponent* CapsuleComponent = YggCharacter->GetAttackCapsuleComponent(CollisionMapKey);
			if (CapsuleComponent)
			{
				CapsuleComponent->CollisionOff();
			}
		}, Duration, false);		
	}
}

