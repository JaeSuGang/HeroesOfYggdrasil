// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
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
	void UpdateTimer();

	void GetStageTimer();

	//void SetPlayerName();

protected:
	void NativeOnInitialized() override;

private:
	//bool bIsVisible = true;
};
