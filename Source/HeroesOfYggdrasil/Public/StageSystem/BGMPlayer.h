// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "StageSystem/StageSystem.h"
#include "BGMPlayer.generated.h"

class UStageBase;

UCLASS()
class HEROESOFYGGDRASIL_API ABGMPlayer : public AActor
{
	GENERATED_BODY()
	
public:	
	ABGMPlayer();

protected:
	virtual void BeginPlay() override;

public:
	UFUNCTION()
	void PlayBGM(int SoundIndex);

	UFUNCTION()
	void OnStartStage(UStageBase* NewStage, int NewRound);

	UFUNCTION()
	void OnGameVictory(FOnVictoryParams OnVictoryParams);

	UFUNCTION()
	void OnGameDefeated(FOnDefeatedParams OnDefeatedParams);

public:	
	UPROPERTY(EditAnywhere)
	UAudioComponent* AudioComponent;

	UPROPERTY(EditAnywhere)
	TArray<USoundWave*> BackgroundMusics;

};
