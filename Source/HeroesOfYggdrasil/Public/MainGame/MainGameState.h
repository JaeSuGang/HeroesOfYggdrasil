// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "Core/YggGameState.h"
#include "MainGameState.generated.h"

/**
 * 담당 코더 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API AMainGameState : public AYggGameState
{
	GENERATED_BODY()
	
public:
	UFUNCTION(NetMulticast, Reliable)
	void OnEnterReadyFinishedGameState();
};
