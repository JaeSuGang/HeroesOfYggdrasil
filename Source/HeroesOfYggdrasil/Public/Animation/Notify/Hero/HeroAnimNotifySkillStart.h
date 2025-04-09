// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "HeroAnimNotifySkillStart.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Hero | Skill Start"))
class HEROESOFYGGDRASIL_API UHeroAnimNotifySkillStart : public UAnimNotify
{
	GENERATED_BODY()
public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
	
};
