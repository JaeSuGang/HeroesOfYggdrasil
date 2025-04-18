// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AuroraSpawnOrbNotify.generated.h"

/**
 * 
 */
class AAuroraOrb;

UCLASS(meta = (DisplayName = "Aurora | SpawnOrb"))
class HEROESOFYGGDRASIL_API UAuroraSpawnOrbNotify : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<AAuroraOrb> OrbClass;
};
