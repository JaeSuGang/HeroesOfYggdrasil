// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AuroraSpawnCatalystNotify.generated.h"

/**
 * 
 */
class AAuroraFrostCatalyst;

UCLASS(meta = (DisplayName = "Aurora | Spawn Catalyst"))
class HEROESOFYGGDRASIL_API UAuroraSpawnCatalystNotify : public UAnimNotify
{
	GENERATED_BODY()

	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;


public:
	UPROPERTY(EditAnywhere, Category = "Aurora")
	TSubclassOf<AAuroraFrostCatalyst> BPCatalyst;
};
