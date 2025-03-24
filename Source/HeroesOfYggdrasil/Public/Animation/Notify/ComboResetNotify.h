// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ComboResetNotify.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Hero | Combo Reset"))
class HEROESOFYGGDRASIL_API UComboResetNotify : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
