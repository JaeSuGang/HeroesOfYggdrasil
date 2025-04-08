// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "YggDeathNotify.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Ygg | Death"))
class HEROESOFYGGDRASIL_API UYggDeathNotify : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	FTimerHandle TimerHandle;
};
