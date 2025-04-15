// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "EnemyAnimNotify_DragonBreath.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UEnemyAnimNotify_DragonBreath : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;
};
