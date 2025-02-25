// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "MainGameState.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API AMainGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	UFUNCTION(NetMulticast, Reliable)
	void OnEnterReadyFinishedGameState();
};
