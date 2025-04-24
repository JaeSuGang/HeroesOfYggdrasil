// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AuroraSkillRNotify.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Aurora | SkillR"))
class HEROESOFYGGDRASIL_API UAuroraSkillRNotify : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	FTimerHandle FreezeTimerHandle;
};
