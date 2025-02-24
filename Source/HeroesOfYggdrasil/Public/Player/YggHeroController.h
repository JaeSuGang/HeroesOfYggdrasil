// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "YggHeroController.generated.h"

UCLASS()
class HEROESOFYGGDRASIL_API AYggHeroController : public APlayerController
{
    GENERATED_BODY()

protected:
    virtual void SetupInputComponent() override;
    virtual void BeginPlay() override;

protected:
   

public:
    
};
