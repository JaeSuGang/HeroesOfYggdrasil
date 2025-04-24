// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AuroraSkillRNotify.generated.h"

/**
 * 
 */
class AEnemyCharacter;

UCLASS(meta = (DisplayName = "Aurora | SkillR"))
class HEROESOFYGGDRASIL_API UAuroraSkillRNotify : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

	TMap<TWeakObjectPtr<AEnemyCharacter>, FTimerHandle> ActiveStunTimers;
};
