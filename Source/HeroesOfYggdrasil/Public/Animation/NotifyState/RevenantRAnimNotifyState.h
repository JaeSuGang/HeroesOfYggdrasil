// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "RevenantRAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API URevenantRAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference);
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AYggProjectileActor> ProjectileClass;

	int32 Count = 10;
	int32 CurCount = 0;

	float Delay = 0.1f;
	float ElapsedTime = 0.0f;
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float CastingTime;

};
