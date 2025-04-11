// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GreystoneSkillRBuffNotify.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Greystone | Skill R Buff"))
class HEROESOFYGGDRASIL_API UGreystoneSkillRBuffNotify : public UAnimNotify
{
	GENERATED_BODY()
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
