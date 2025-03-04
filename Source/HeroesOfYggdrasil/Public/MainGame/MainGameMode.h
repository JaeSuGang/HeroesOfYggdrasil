// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "MainGameMode.generated.h"

class APlayerSelectZone;

/**
 * 담당 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API AMainGameMode : public AGameMode
{
	GENERATED_BODY()
	
protected:
	void InitGameState() override;

	void BeginPlay() override;

	void PostLogin(APlayerController* PC) override;

	void Logout(AController* controller) override;

protected:
	TArray<int> AvailablePlayerIds;

	TArray<int> OccupiedPlayerIds;
};
