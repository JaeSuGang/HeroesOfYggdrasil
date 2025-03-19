// Coded By AssortRock Unreal Engine Class Project


#include "Animation/NotifyState/YggAnimNotifyState_Attack.h"


#include "Player/YggHero.h"
#include "Attribute/HeroAttributeComponent.h"
#include "Animation/YggHeroAnimInstance.h"


void UYggAnimNotifyState_Attack::NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyBegin(MeshComp, Animation, TotalDuration, EventReference);
}

void UYggAnimNotifyState_Attack::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
}

void UYggAnimNotifyState_Attack::NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyEnd(MeshComp, Animation, EventReference);
	AYggHero* Hero = Cast<AYggHero>(MeshComp->GetOwner());
	if (!Hero)
	{
		return;
	}
	UHeroAttributeComponent* HeroAttributeComponent = Hero->GetHeroAttributeComponent();
	UYggHeroAnimInstance* HeroAnimInstance = Hero->GetHeroAnimInstance();

	if (HeroAttributeComponent&& HeroAnimInstance)
	{
		if (false == HeroAttributeComponent->HasTagExact(TEXT("Character.State.PressedAttack"))) 
		{
			HeroAttributeComponent->RemoveTag(TEXT("Character.State.NotAttackable"));
			HeroAnimInstance->StopMontage();
		}
	}
}
