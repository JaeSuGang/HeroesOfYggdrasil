// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GreystoneRLand.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Greystone | Land"))
class HEROESOFYGGDRASIL_API UGreystoneRLand : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
