// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "YggHeroInterface.generated.h"

UINTERFACE(MinimalAPI, BlueprintType)
class UYggHeroInterface : public UInterface
{
	GENERATED_BODY()	
};

class HEROESOFYGGDRASIL_API IYggHeroInterface
{
    GENERATED_BODY()

public:
    virtual void MagicCircleOn() = 0;
    virtual void MagicCircleOff() = 0;
};