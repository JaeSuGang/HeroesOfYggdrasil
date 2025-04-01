// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "YggParticleNotify.generated.h"

/**
 * 
 */
class UNiagaraSystem;

USTRUCT(BlueprintType)
struct FSkills
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Skill Q"))
	bool SkillQ = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Skill E"))
	bool SkillE = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (DisplayName = "Skill R"))
	bool SkillR = false;
};

UCLASS(meta = (DisplayName = "Ygg | Particle"))
class HEROESOFYGGDRASIL_API UYggParticleNotify : public UAnimNotify
{
	GENERATED_BODY()
	
	virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

#if WITH_EDITOR
	virtual void PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent) override;
#endif

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggParticleSystem", meta = (DisplayName = "Particle System"))
	TObjectPtr<UParticleSystem> DelayedPSTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggParticleSystem", meta = (DisplayName = "Particle System"))
	TObjectPtr<UParticleSystem> PSTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggParticleSystem", meta = (DisplayName = "Niagara System", ToolTip = "The niagara system to spawn for the notify state"))
	TObjectPtr<UNiagaraSystem> NSTemplate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggParticleSystem")
	float DelayTime;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggParticleSystem")
	float Duration;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "YggParticleSystem", meta = (DisplayName = "Skills", ShowOnlyInnerProperties))
	FSkills Skills;
};
