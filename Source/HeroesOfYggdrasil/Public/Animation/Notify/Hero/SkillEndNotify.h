// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "SkillEndNotify.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Hero | Skill End"))
class HEROESOFYGGDRASIL_API USkillEndNotify : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
