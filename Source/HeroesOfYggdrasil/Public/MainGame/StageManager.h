// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "StageManager.generated.h"

/**
 * 담당 코더 : 김경민
 */
UCLASS(Blueprintable, BlueprintType)
class HEROESOFYGGDRASIL_API AStageManager : public AInfo
{
	GENERATED_BODY()
	

public:
	AStageManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
