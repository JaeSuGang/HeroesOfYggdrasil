// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AuroraThrowCatalystNotify.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Aurora | Throw Catalyst"))
class HEROESOFYGGDRASIL_API UAuroraThrowCatalystNotify : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
