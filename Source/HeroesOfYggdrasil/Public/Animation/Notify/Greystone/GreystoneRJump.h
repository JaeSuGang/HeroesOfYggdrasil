// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GreystoneRJump.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Greystone | Jump"))
class HEROESOFYGGDRASIL_API UGreystoneRJump : public UAnimNotify
{
	GENERATED_BODY()
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	FTimerHandle JumpTimerHandle;
};
