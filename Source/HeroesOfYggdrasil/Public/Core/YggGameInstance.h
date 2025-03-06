// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "YggGameInstance.generated.h"

/**
 * 담당 코더 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggGameInstance : public UGameInstance
{
	GENERATED_BODY()
	

public:
	UPROPERTY()
	FString LocalPlayerName;
};
