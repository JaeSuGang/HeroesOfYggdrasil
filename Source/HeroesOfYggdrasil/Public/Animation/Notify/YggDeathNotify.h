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

	UMaterialInstanceDynamic* DynamicMatInstance;
	float CurrentLerpValue = 0.0f;
	float LerpDuration = 2.0f; // 2초 동안 변화
	FTimerHandle TimerHandle;
};
