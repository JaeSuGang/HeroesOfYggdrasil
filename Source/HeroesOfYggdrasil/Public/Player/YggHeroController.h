// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "GenericTeamAgentInterface.h"
#include "YggHeroController.generated.h"

UCLASS()
class HEROESOFYGGDRASIL_API AYggHeroController : public APlayerController, public IGenericTeamAgentInterface
{
    GENERATED_BODY()

protected:
    virtual void SetupInputComponent() override;
    virtual void BeginPlay() override;

    virtual FGenericTeamId GetGenericTeamId() const override;
    FGenericTeamId HeroTeamID;

protected:
   

public:
    
};
