// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "StageSystem/StageBase.h"
#include "BattleStage.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UBattleStage : public UStageBase
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere)
	UDataTable* WaveTable;
};
