// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AuroraScreenParticleNotify.generated.h"

/**
 * 
 */
UCLASS(meta = (DisplayName = "Aurora | Screen Particle"))
class HEROESOFYGGDRASIL_API UAuroraScreenParticleNotify : public UAnimNotify
{
	GENERATED_BODY()

public:
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aurora|Particle")
    UParticleSystem* ParticleTemplate;

    /**
     * 카메라 기준 생성 위치 오프셋
     */
    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Aurora|Particle")
    FVector LocationOffset = FVector(40.0f, 0.0f, 0.0f);

    /**
     * 노티파이 실행 시 호출됨
     */
    virtual void Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation) override;

};
