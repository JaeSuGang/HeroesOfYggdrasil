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
	void PostLogin(APlayerController* PC) override;

public:
	void OnAllPlayersReady();


public:
	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<APawn> MainPawn;

	UPROPERTY(EditAnywhere, Category = YGG)
	TSubclassOf<AActor> SelectZone;

	UPROPERTY(EditAnywhere, Category = YGG)
	FVector SelectZoneLocation;

	UPROPERTY(EditAnywhere, Category = YGG)
	FRotator SelectZoneRotation;

	UPROPERTY(EditAnywhere, Category = YGG)
	FVector SelectZonePosOffset;

	UPROPERTY(VisibleInstanceOnly, Category = YGG)
	TArray<APlayerSelectZone*> PlayerZones;
};
