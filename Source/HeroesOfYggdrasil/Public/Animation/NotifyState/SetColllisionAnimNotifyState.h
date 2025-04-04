// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "SetColllisionAnimNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API USetColllisionAnimNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()

public:
	virtual void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	virtual void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;




	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName CollisionMapKey;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bEndWithTimer = false;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Duration = 0.0f;

};
