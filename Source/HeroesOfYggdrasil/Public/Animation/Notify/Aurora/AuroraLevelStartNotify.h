// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AuroraLevelStartNotify.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Aurora | Level Start"))
class HEROESOFYGGDRASIL_API UAuroraLevelStartNotify : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
