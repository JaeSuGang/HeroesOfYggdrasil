// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GreystoneRollEndNotify.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Greystone | Roll End"))
class HEROESOFYGGDRASIL_API UGreystoneRollEndNotify : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
