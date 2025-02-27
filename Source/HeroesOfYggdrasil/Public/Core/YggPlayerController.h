// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
#include "YggPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API AYggPlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AYggPlayerController(const FObjectInitializer& ObjectInitializer = FObjectInitializer::Get());

public:
	FGenericTeamId GetGenericTeamId() const override;

protected:
	FGenericTeamId TeamID;
};
