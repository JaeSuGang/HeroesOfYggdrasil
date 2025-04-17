// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "HeroSkillCastingNotify.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Hero | SkillCasting"))
class HEROESOFYGGDRASIL_API UHeroSkillCastingNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

	UPROPERTY()
	float SkillCastingTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SkillQ = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SkillE = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool SkillR = false;

	FTimerHandle CastingTimerHandle;
};
