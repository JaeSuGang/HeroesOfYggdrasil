// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "EnemyAnimNotify_Damage.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UEnemyAnimNotify_Damage : public UAnimNotifyState
{
	GENERATED_BODY()
public:
	UPROPERTY(Category = "YggNotify", EditAnywhere, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	FName CollisionProfileName;

	void NotifyBegin(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float TotalDuration, const FAnimNotifyEventReference& EventReference) override;
	void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;
	void NotifyEnd(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, const FAnimNotifyEventReference& EventReference) override;
};
