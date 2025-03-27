// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "GreystoneComboNotify.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Greystone | Combo"))
class HEROESOFYGGDRASIL_API UGreystoneComboNotify : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

private:
	int MaxCombo = 3;
};
