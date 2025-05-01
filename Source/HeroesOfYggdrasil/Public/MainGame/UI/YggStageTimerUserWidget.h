// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "StageSystem/StageBase.h"
#include "YggStageTimerUserWidget.generated.h"

class UTextBlock;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggStageTimerUserWidget : public UYggUserWidget
{
	GENERATED_BODY()

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* StageTimer;

	UFUNCTION(BlueprintCallable)
	void UpdateTimer(UStageBase* NewStage, int NewRound);

	void GetStageTimer();

	//void SetPlayerName();

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;


private:
	//bool bIsVisible = true;
};
