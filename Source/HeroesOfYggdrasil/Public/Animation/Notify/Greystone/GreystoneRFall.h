// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GreystoneRFall.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Greystone | Fall"))
class HEROESOFYGGDRASIL_API UGreystoneRFall : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;	
};
