// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "StageDataAsset.generated.h"

/**
 * 담당 코더 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API UStageDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	/* 데이터 에셋 이름을 기준으로 PrimaryAssetID 생성 */
	virtual FPrimaryAssetId GetPrimaryAssetId() const override;

public:
	UPROPERTY(EditAnywhere)
	float Timer;
};
