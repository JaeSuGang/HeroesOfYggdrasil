// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "PlayerManager.generated.h"

/**
 * 담당 코더 : 김경민
 */
UCLASS(Blueprintable)
class HEROESOFYGGDRASIL_API APlayerManager : public AInfo
{
	GENERATED_BODY()
	
public:
	APlayerManager(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());
};
