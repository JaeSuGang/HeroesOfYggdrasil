// Coded By AssortRock Unreal Engine Class Project

#pragma once

#include "CoreMinimal.h"
#include "MainGame/UI/YggUserWidget.h"
#include "YggWavePopupUserWidget.generated.h"

class UStageBase;
class UTextBlock;
class UWidgetAnimation;

/**
 * 
 */
UCLASS()
class HEROESOFYGGDRASIL_API UYggWavePopupUserWidget : public UYggUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION()
	void UpdateWidget(UStageBase* NewStage);

	UFUNCTION()
	void EndAnim();

protected:
	virtual void NativeOnInitialized() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Wave;

	UPROPERTY(meta = (BindWidgetAnim), Transient)
	UWidgetAnimation* WaveAnim;

	FWidgetAnimationDynamicEvent EndDelegate;

};
