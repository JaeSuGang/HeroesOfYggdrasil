// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "HeroJumpTraceNotifyState.generated.h"

/**
 * 
 */
class AYggHero;

UCLASS()
class HEROESOFYGGDRASIL_API UHeroJumpTraceNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);
	
	TObjectPtr<AYggHero> Hero;
	FVector StartLocation;
	FVector TargetLocation;

	float ElapsedTime = 0.0f;
	float MoveDuration = 0.8f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float JumpHeight;
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Scope;

};
