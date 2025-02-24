// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameGamemode.generated.h"

/**
 * 담당 : 김경민
 */
UCLASS()
class HEROESOFYGGDRASIL_API AMainGameGamemode : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	AMainGameGamemode();

protected:
	void PostLogin(APlayerController* PC) override;

	void BeginPlay() override;

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
};
