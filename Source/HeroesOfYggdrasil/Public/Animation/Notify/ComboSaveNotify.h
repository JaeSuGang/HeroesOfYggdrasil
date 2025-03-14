// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "ComboSaveNotify.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Hero | Combo Save"))
class HEROESOFYGGDRASIL_API UComboSaveNotify : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
